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

class AddPositionHandler(AbstractHandler):
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

		state = self.__add_position_to_db(json_data)
		if not state:
			res.status_code=500 #TODO
			res.data = json.dumps({"error" : "insertion failed"})
			return

		res.status_code=200
	
	def __add_position_to_db(self, json):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

		str_query = self.__get_str_query(json)

		query = DBQuery(conn)
		if not query.exec_query(str_query):
			print(query.get_error())
			return False	

		access_manager.disconnect(conn_name)
		return True
	
	def __get_str_query(self, json_data):
		str_query = \
			'''INSERT INTO position (title, salary) VALUES ('{t}', {s});'''\
				.format(t=json_data['title'], s=json_data['salary'])
		return str_query

	def check_json(self, json_data : dict):
		state = True
		fields = [	'title',
					'salary']

		for field in fields:
			state = state and json_data.__contains__(field)

		return state
		