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

class AddStaffHandler(AbstractHandler):
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

		if not self.check_json(json_data):
			res.status_code=403
			res.data = json.dumps({"error" : "Expected values was not received"})
			return

		state = self.__insert_staff_to_db(json_data)
		if not state:
			res.status_code=500
			res.data = json.dumps({"error" : "insertion failed"})
			return

		res.status_code=201
	
	def __insert_staff_to_db(self, json):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

		str_query_passport = self.__get_str_query_passport(json['passport'])

		query = DBQuery(conn)
		query.begin_transaction()
		if not query.exec_query(str_query_passport):
			print(query.get_error())
			query.rollback_transaction()
			return False, None
		else:
			result = query.get_values()
		
		pass_id = str(result[0][0])
		print(pass_id)

		str_query_staff = self.__get_str_query_staff(json, pass_id)

		if not query.exec_query(str_query_staff):
			print(query.get_error())
			query.rollback_transaction()
			return False
		else:
			res = query.get_values()
		
		staff_id = str(res[0][0])
		
		for sched_item in json['schedule']:
			str_query_sched = self.__get_str_query_sched(sched_item, staff_id)
			if not query.exec_query(str_query_sched):
				print(query.get_error())
				query.rollback_transaction()
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


	def __get_str_query_staff(self, json : dict, pass_id : int):
		pos_id = json['position']['pos_id']
		fire = json['fire_date']
		if len(fire) == 0:
			fire = 'NULL'
		q = '''INSERT INTO staff (passport, position, edu_level, fire_date, employ_date)
			VALUES ({pas}, {pos}, '{edu}', {f}, '{empl}') RETURNING staff_id;'''\
			.format(pas=pass_id, pos=pos_id, edu=json['edu_level'], f=fire, empl=json['employ_date'])
		return q
	
	def __get_str_query_passport(self, passport : dict):
		q = '''INSERT INTO passports (surname, name, patronymic, sex, birth, num, issue_date, nationality)
			VALUES ('{sur}', '{name}', '{patr}', '{s}', '{b}', '{n}', '{iss}', '{nat}') RETURNING pass_id;'''.format(sur=passport['surname'], name=passport['name'],
			patr=passport['patronymic'], s=passport['sex'], b=passport['birth'],
			n=passport['num'], iss=passport['issue_date'], nat=passport['nationality'])
		return q


	def check_json(self, json_data : dict):
		state = True
		fields = [  'passport',
					'position',
					'edu_level',
					'fire_date',
					'employ_date']
		passport_fields = [	'surname',
							'name',
							'patronymic',
							'sex',
							'birth',
							'num',
							'issue_date',
							'nationality' ]
		position_fields = [	'pos_id' ]
		sched_fields = [	'day_of_week',
							'start',
							'end',
							'cabinet'	]

		for field in fields:
			state = state and json_data.__contains__(field)
			if not state:
				return False
		
		passport = json_data['passport']
		for field in passport_fields:
			state = state and passport.__contains__(field)
			if not state:
				return False
		
		position = json_data['position']
		for field in position_fields:
			state = state and position.__contains__(field)
			if not state:
				return False
		sched = json_data['schedule']
		for item in sched:
			for field in sched_fields:
				state = state and item.__contains__(field)
				if not state:
					return False
		
		return state
		