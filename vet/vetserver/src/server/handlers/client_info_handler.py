from .abstract_handler import AbstractHandler

from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker

import json
import uuid

class ClientInfoHandler(AbstractHandler):
	def request(self, req, res):
		# key = str(req.headers.get("Authorization"))
		# # Authorization: Explicit Key
		# explicit_key="Explicit: "
		# idx = key.find(explicit_key) 
		# if idx == -1:
		# 	print("Index: {idx}, Key: {key}".format(idx=idx, key=key))
		# 	res.status_code=401
		# 	return
		
		# key = key[len(explicit_key):]
		# staff_id = valid_key_checker.get_owner(key)
		# if staff_id == -1:
		# 	res.status_code=401
		# 	return

		if req.method == "GET":
			id = req.args.get("id", default=None, type=None)
			status, data = self.__get_request(id)
			if not status:
				res.status_code=500
				return
			else:
				res.data = json.dumps(data)
				res.status_code=200
				res.content_type="application/json"
				return
		elif req.method == "POST":
			json_data = json.loads(req.data)
			if self.__post_request(json_data):
				res.status_code = 201
			else:
				res.status_code = 500
			return
		elif req.method == "PUT":
			json_data = json.loads(req.data)
			if self.__put_request(json_data):
				res.status_code = 200
			else:
				res.status_code = 500
			return
			

	def __post_request(self, json_data : dict):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

		query = DBQuery(conn)
		query.begin_transaction()
		address=json_data["address"]
		address_id : int
		str_query = \
			'''INSERT INTO addresses (country, city, street, house, flat)
					VALUES('{country}', '{city}', '{street}', '{house}', '{flat}') RETURNING addr_id;'''\
				.format(country=address["country"], city=address['city'], street=address['street'],
					house=address['house'], flat=address['flat'], id=address['addr_id'])
		if not query.exec_query(str_query):
			print(query.get_error())
			query.rollback_transaction()
			return False
		else:
			address_id = query.get_values()[0][0]

		passport=json_data["passport"]
		passport_id : int
		str_query = \
			'''INSERT INTO passports (surname, name, patronymic, sex, birth, num, issue_date, nationality) 
				VALUES ('{sn}', '{nm}', '{pt}', '{sx}', '{bd}'::date, '{nu}', '{is_}'::date, '{nt}') RETURNING pass_id;''' \
						.format(sn=passport["surname"], nm=passport['name'], pt=passport['patronymic'], sx=passport['sex'], bd=passport["birth"],
							nu=passport["num"].replace(' ', ''), is_=passport["issue_date"], nt=passport["nationality"], id=passport["pass_id"])
		if not query.exec_query(str_query):
			print(query.get_error())
			query.rollback_transaction()
			return False
		else:
			passport_id = query.get_values()[0][0]

		str_query = \
			'''INSERT INTO clients (contacts, address, passport) VALUES ('{cont_json}', {addr_id}, {pass_id});'''\
				.format(cont_json=json.dumps(json_data["contacts"]), addr_id=address_id, pass_id=passport_id)
		if not query.exec_query(str_query):
			print(query.get_error())
			query.rollback_transaction()
			return False

		query.commit_transaction()
		access_manager.disconnect(conn_name)
		return True


	def __put_request(self, json_data: dict):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

		str_query = \
			'''UPDATE clients SET contacts='{cont_json}' WHERE cli_id={id};'''\
				.format(cont_json=json.dumps(json_data["contacts"]), id=json_data['cli_id'])
		query = DBQuery(conn)
		query.begin_transaction()
		if not query.exec_query(str_query):
			print(query.get_error)
			query.rollback_transaction()
			return False
		
		address=json_data["address"]
		str_query = \
			'''UPDATE addresses SET country='{country}', city='{city}', street='{street}', house='{house}', flat='{flat}' WHERE addr_id={id};'''\
				.format(country=address["country"], city=address['city'], street=address['street'],
					house=address['house'], flat=address['flat'], id=address['addr_id'])
		if not query.exec_query(str_query):
			print(query.get_error)
			query.rollback_transaction()
			return False

		passport=json_data["passport"]
		str_query = \
			'''UPDATE passports 
				SET surname='{sn}', name='{nm}', patronymic='{pt}', sex='{sx}', birth='{bd}'::date, 
					num='{nu}', issue_date='{is_}'::date, nationality='{nt}' WHERE pass_id={id};''' \
						.format(sn=passport["surname"], nm=passport['name'], pt=passport['patronymic'], sx=passport['sex'], bd=passport["birth"],
							nu=passport["num"].replace(' ', ''), is_=passport["issue_date"], nt=passport["nationality"], id=passport["pass_id"])
		if not query.exec_query(str_query):
			print(query.get_error())
			query.rollback_transaction()
			return False

		query.commit_transaction()
		access_manager.disconnect(conn_name)
		return True

	def __get_request(self, id : int):
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
