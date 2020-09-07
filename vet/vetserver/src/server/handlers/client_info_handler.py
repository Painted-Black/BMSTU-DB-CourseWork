from .abstract_handler import AbstractHandler

from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker

import json
import uuid

class ClientInfoHandler(AbstractHandler):
	def request(self, req, res):
		key = str(req.headers.get("Authorization"))
		# Authorization: Explicit Key
		explicit_key="Explicit: "
		idx = key.find(explicit_key) 
		if idx == -1:
			print("Index: {idx}, Key: {key}".format(idx=idx, key=key))
			res.status_code=401
			return
		
		key = key[len(explicit_key):]
		staff_id = valid_key_checker.get_owner(key)
		if staff_id == -1:
			res.status_code=401
			return

		id = req.args.get("id", default=None, type=None)
		status, data = self.__queryDb(id)
		if not status:
			res.status_code=500
			return

		res.data = json.dumps(data)
		res.status_code=200

	def __queryDb(self, id : int):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = \
			'SELECT * FROM clients LEFT JOIN passports ON passport=pass_id LEFT JOIN addresses ON address=addr_id WHERE cli_id={};'\
				.format(id)
		query = DBQuery(conn)
		if not query.exec_query(str_query):
			print(query.get_error())
			return False, ""
		else:
			result = query.get_values()

		access_manager.disconnect(conn_name)
		return True, self.__to_json(result[0], query.get_column_names())

	def __to_json(self, data : list, columns : list):
		client={}
		address={}
		passport={}

		for i in range(0, 4):
			client[columns[i]]=str(data[i])

		for i in range(4, 13):
			passport[columns[i]]=str(data[i])

		for i in range(13, len(data)):
			address[columns[i]]=str(data[i])
		
		client["passport"] = passport
		client["address"] = address

		return client
