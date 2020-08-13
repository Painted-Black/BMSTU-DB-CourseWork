from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
import json
import uuid

from flask import request

class AuthHandler(AbstractHandler):
	def request(self, req, res):
		res.content_type = "Application/Json"

		try:
			auth_data = json.loads(req.data)
		except json.decoder.JSONDecodeError:
			res.status_code=403
			res.data = json.dumps({"error" : "Empty fields"})
			return

		if not auth_data.__contains__('login')  or \
			not auth_data.__contains__('password'):
			res.status_code=403
			res.data = json.dumps({"error" : "Expected values was not received"})
			return

		state, data = self.__queryDb(auth_data['login'], auth_data['password'])
		if (not state):
			res.status_code=403
			res.data = json.dumps({"error" : "invalid fields"})
			return

		key = str(uuid.uuid4())
		data[0]["key"] = key

		json_data = json.dumps(data)
		staff_id=data[0]["staff_id"]
		valid_key_checker.register_key(key, staff_id)

		res.data = json_data

	def __to_json(self, rows, column_names):
		arr = []
		l = len(column_names)
		for i in rows:
			d = {}
			for j in range (l):
				d[column_names[j]] = str(i[j])
			arr.append(d)
		print(arr)
		return arr

	def __queryDb(self, login, passw):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = "SELECT a.login, a.access_level, s.*, p.*, ps.* FROM staff s LEFT JOIN access a ON s.staff_id=a.employee JOIN position p ON position=p.pos_id JOIN passports ps ON s.passport=ps.pass_id WHERE a.login='{}' AND a.password='{}';".format(login, passw)
		query = DBQuery(conn, str_query)
		if not query.execQuery():
			return False, None
		else:
			result = query.get_values()

		if len(result) == 0:
			return False, None

		access_manager.disconnect(conn_name)
		return True, self.__to_json(result, query.get_colunm_names())