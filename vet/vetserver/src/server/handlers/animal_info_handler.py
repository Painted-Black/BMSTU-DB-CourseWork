from .abstract_handler import AbstractHandler
from .utils import *

from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker

import json
import uuid

class AnimalInfoHandler(AbstractHandler):
	def request(self, req, res):
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

		id = req.args.get("id", default=None, type=None)
		status, data = self.__queryDb(id)
		if not status:
			res.status_code=500
			return

		status, client_data = self.__query_client(int(data["contract"]["owner"]))
		if not status:
			res.status_code=500
			return

		data["contract"]["owner"] = client_data

		res.data = json.dumps(data)
		res.status_code=200

	def __queryDb(self, id : int):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = '''SELECT * FROM animals_medical_records a 
							LEFT JOIN contract ON contract=contr_id 
							LEFT JOIN microchips m ON a.chip_id=m.chip_id 
								WHERE anim_id={};'''.format(id)
		query = DBQuery(conn)
		if not query.exec_query(str_query):
			return False, ""
		else:
			result = query.get_values()

		access_manager.disconnect(conn_name)
		return True, self.__to_json(result, query.get_column_names())

	def __query_client(self, id : int):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = '''SELECT * FROM clients c 
						LEFT JOIN passports ON passport=pass_id 
						LEFT JOIN addresses ON address=addr_id 
							WHERE cli_id={};'''.format(id)
		query = DBQuery(conn)
		if not query.exec_query(str_query):
			return False, ""
		else:
			result = query.get_values()

		access_manager.disconnect(conn_name)
		return True, self.__to_json_client(result, query.get_column_names())


	def __to_json(self, rows : list, column_names : list):
		row = rows[0]
		animal_info = {}
		for i in range(0, 14):
			animal_info[column_names[i]]=str(row[i])

		contract = {}
		for i in range(14, 20):
			contract[column_names[i]] = str(row[i])

		chips = {}
		for i in range(20, len(row)):
			chips[column_names[i]] = str(row[i])

		animal_info["contract"] = contract
		animal_info["chip_id"] = chips
		
		return animal_info

	def __to_json_client(self, rows : list, column_names : list):
		row = rows[0]
		client = {}
		for i in range(0, 4):
			client[column_names[i]] = str(row[i])

		passport={}		
		for i in range(4, 13):
			passport[column_names[i]] = str(row[i])

		address={}
		for i in range(13, len(row)):
			address[column_names[i]] = str(row[i])

		client["passport"] = passport
		client["address"] = address

		return client