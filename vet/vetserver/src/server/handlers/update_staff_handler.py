from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
from server.utils.animal_state import AnimalState
import json
import uuid
from flask import request
from server.utils.visit import Visit

class UpdateStaffHandler(AbstractHandler):
	def request(self, req, res):
		res.content_type = "application/json"
		try:
			json_data = json.loads(req.data)
		except json.decoder.JSONDecodeError:
			res.status_code=403
			res.data = json.dumps({"error" : "Empty json"})
			return
		
		key = str(req.headers.get("Authorization"))
		# Authorization: Explicit Key
		explicit_key="Explicit: "
		idx = key.find(explicit_key) 
		if idx == -1:
			res.status_code=401
			return
		
		key = key[len(explicit_key):]
		staff_id = valid_key_checker.get_owner(key)
		if staff_id == -1:
			res.status_code=401
			return

		_type = req.args.get("type", default=None, type=None)

		if _type != "passport" and _type != "staff" and _type != "schedule":
			res.status_code=400
			return

		str_query=""

		if _type == "passport":
			if not self.check_passport_json(json_data):
				res.status_code=403
				res.data = json.dumps({"error" : "Expected values was not received"})
				return
			str_query = self.__get_str_query_passport(json_data)

			state = self.__update_db(str_query)
			if not state:
				res.status_code=500
				res.data = json.dumps({"error" : "update failed"})
				return
		
		elif _type == "staff":
			if not self.check_staff_json(json_data):
				res.status_code=403
				res.data = json.dumps({"error" : "Expected values was not received"})
				return
			str_query = self.__get_str_query_staff(json_data)

			state = self.__update_db(str_query)
			if not state:
				res.status_code=500
				res.data = json.dumps({"error" : "update failed"})
				return

		elif _type == "schedule":
			if not self.check_schedule_json(json_data):
				res.status_code=403
				res.data = json.dumps({"error" : "Expected values was not received"})
				return
			state = self.__update_schedule(json_data)
			if not state:
				res.status_code=500
				res.data = json.dumps({"error" : "insertion failed"})
				return

		res.status_code=201
	
	def __update_schedule(self, json_data):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

		del_q = '''DELETE FROM schedule WHERE employee_id={i};'''\
			.format(i=json_data['employee_id'])

		query = DBQuery(conn)
		query.begin_transaction()
		if not query.exec_query(del_q):
			print(query.get_error())
			query.rollback_transaction()
			access_manager.disconnect(conn_name)
			return False

		schedule = json_data['schedule']
		for s in schedule:
			str_query = self.__get_str_query_sched(s, json_data['employee_id'])
			if not query.exec_query(str_query):
				print(query.get_error())
				query.rollback_transaction()
				access_manager.disconnect(conn_name)
				return False
			
		query.commit_transaction()

		access_manager.disconnect(conn_name)
		return True

	def __get_str_query_sched(self, json : dict, staff_id : int):
		q = '''INSERT INTO schedule (employee_id, day_of_week, start, "end", cabinet)
			VALUES ({empl}, '{day}', '{st}', '{end}', '{cab}');'''\
			.format(empl=staff_id, day=json['day_of_week'], st=json['start'],
			end=json['end'], cab=json['cabinet'])
		return q

	def check_schedule_json(self, json_data):
		state = True
		sched_fields = [	'day_of_week',
							'start',
							'end',
							'cabinet'	]

		state = state and json_data.__contains__('employee_id')
		state = state and json_data.__contains__('schedule')
		if not state:
			return
		
		for json_item in json_data['schedule']:
			for field in sched_fields:
				state = state and json_item.__contains__(field)
				if not state:
					return False
			
		return state
	
	def __update_db(self, str_query : str):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

		query = DBQuery(conn)
		query.begin_transaction()
		if not query.exec_query(str_query):
			print(query.get_error())
			query.rollback_transaction()
			access_manager.disconnect(conn_name)
			return False

		query.commit_transaction()
		access_manager.disconnect(conn_name)
		return True
	
	def __get_str_query_passport(self, json : dict):
		q = '''UPDATE passports SET surname='{sur}', name='{name}', patronymic='{patr}', sex='{sex}',
		birth='{bir}', num='{num}', issue_date='{iss}', nationality='{nat}' 
		WHERE pass_id={id};'''.format(sur=json['surname'], name=json['name'],
		patr=json['patronymic'], sex=json['sex'], bir=json['birth'], 
		num=json['num'], iss=json['issue_date'], nat=json['nationality'],
		id=json['pass_id'])
		return q
	
	def __get_str_query_staff(self, json : dict):
		q = '''UPDATE staff SET edu_level='{edu}', position={pos} WHERE staff_id={id};'''\
			.format(edu=json['edu_level'], pos=json['position'], id=json['staff_id'])
		return q

	def check_staff_json(self, json_data : dict):
		state = True
		staff_fields = [	'staff_id',
							'edu_level',
							'position']

		for field in staff_fields:
			state = state and json_data.__contains__(field)
			if not state:
				return False
			
		return state

	def check_passport_json(self, json_data : dict):
		state = True
		passport_fields = [	'pass_id',
							'surname',
							'name',
							'patronymic',
							'sex',
							'birth',
							'num',
							'issue_date',
							'nationality' ]

		for field in passport_fields:
			state = state and json_data.__contains__(field)
			if not state:
				return False
			
		return state
		