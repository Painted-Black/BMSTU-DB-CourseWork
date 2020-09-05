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

class NewVisitHandler(AbstractHandler):
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

		state = self.__insert_visit_to_json(json_data)
		if not state:
			res.status_code=500 #TODO
			res.data = json.dumps({"error" : "insertion failed"})
			return

		res.status_code=201
	
	def __insert_visit_to_json(self, json):
		animal_state = json['cur_state']
		vis = json
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

		str_query_state = \
			'''INSERT INTO animal_states (general, pulse, weight, ap, temperature, cfr, resp_rate) VALUES ('{}', {}, {}, '{}', {}, {}, {}) RETURNING state_id;'''.format(animal_state['general'], animal_state['pulse'], animal_state['weight'], animal_state['ap'],
			animal_state['temperature'], animal_state['cfr'], animal_state['resp_rate'])

		query = DBQuery(conn)
		if not query.exec_query(str_query_state):
			print(query.get_error())
			return False, None
		else:
			result = query.get_values()
		
		state_id = str(result[0][0])

		if vis['next_visit'] == None:
			next_date = 'NULL'
		else:
			next_date = "'" + vis['next_visit'] + "'"
		str_query_visit = \
			'''INSERT INTO visits (doctor, animal, visit_date, owner_dynamics, history_disease, cur_state, diagnosis, recommendations, next_visit, prescribings, note) VALUES ({}, {}, '{}', '{}', '{}', '{}', '{}', '{}', {}, '{}', '{}');'''.format(
				vis['doctor']['staff_id'],
				vis['animal']['anim_id'],
				vis['visit_date'], 
				vis['owner_dynamics'],
				vis['history_disease'], 
				state_id, 
				vis['diagnosis'], 
				vis['recommendations'], 
				next_date, 
				str(vis['prescribings']).replace("'", '"'), 
				vis['note'])

		query = DBQuery(conn)
		if not query.exec_query(str_query_visit):
			print(query.get_error())
			return False

		access_manager.disconnect(conn_name)
		return True

	def check_json(self, json_data : dict):
		state = True
		fields = [  'doctor',		 
					'animal',		  
					'visit_date',	 
					'owner_dynamics', 
					'history_disease',
					'cur_state',	  
					'diagnosis',	  
					'recommendations',
					'next_visit',	 
					'prescribings',	   
					'note']

		for field in fields:
			state = state and json_data.__contains__(field)

		return state
		