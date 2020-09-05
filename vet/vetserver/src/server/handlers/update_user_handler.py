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

class UpdateUserHandler(AbstractHandler):
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

		state = self.__update_user_in_db(json_data)
		if not state:
			res.status_code=500 #TODO
			res.data = json.dumps({"error" : "insertion failed"})
			return

		res.status_code=200
	
	def __update_user_in_db(self, json):
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
			'''UPDATE access SET '''
		if (json_data.__contains__('login')):
			str_query += '''login='{l}','''.format(l=json_data['login'])
		if (json_data.__contains__('password')):
			str_query += ''' password='{p}','''.format(p=json_data['password'])
		if (json_data.__contains__('access_level')):
			str_query += " access_level='{a}'".format(a=json_data['access_level'])
		if (str_query[-1]==','):
			str_query=str_query[:-1]
		str_query += ''' WHERE acc_id={i};'''.format(i=json_data['acc_id'])
		return str_query

	def check_json(self, json_data : dict):
		state = True

		state = state and json_data.__contains__('acc_id')
		state = state and (json_data.__contains__('login') \
							or json_data.__contains__('password')\
							or json_data.__contains__('access_level'))

		return state
		