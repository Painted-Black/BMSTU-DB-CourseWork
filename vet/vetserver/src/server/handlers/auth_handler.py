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

		state, data = self.__query_staff_data_from_db(auth_data['login'], auth_data['password'])
		if (not state):
			res.status_code=403
			res.data = json.dumps({"error" : "invalid fields"})
			return

		key = str(uuid.uuid4())
		data["key"] = key
		staff_id=data["employee"]["staff_id"]

		state, schedule = self.__query_staff_schedule(staff_id)
		if (not state):
			res.status_code=500
			return

		data["employee"]["schedule"] = schedule

		json_data = json.dumps(data)
		valid_key_checker.register_key(key, staff_id)

		res.data = json_data

	def __to_json_schedule(self, rows, column_names):
		arr = []
		l = len(column_names)
		for i in rows:
			d = {}
			d[column_names[0]] = str(i[0])
			for j in range (2, l):
				d[column_names[j]] = str(i[j])
			arr.append(d)
		return arr
    			



	def __to_json_staff_schedule(self, rows, column_names):
		out_json_obj = {}
		row = rows[0]
		for access in range(0, 2):
			out_json_obj[column_names[access]] = str(row[access])
			
		passport_json={}
		for ps in range(10, len(row)):
			passport_json[column_names[ps]] = str(row[ps])

		positions_json={}
		for pos in range(7,10):
			positions_json[column_names[pos]] = str(row[pos])

		staff_json={}
		for staff in range(2, 7):
			staff_json[column_names[staff]] = str(row[staff])
		
		positions_json["passport"] = passport_json
		staff_json["position"] = positions_json
		out_json_obj["employee"] = staff_json
		return out_json_obj

	def __query_staff_schedule(self, uid):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

		str_query = \
			"""SELECT * FROM schedule WHERE employee_id={}""".format(uid)
		query = DBQuery(conn, str_query)
		if not query.execQuery():
			return False, None
		else:
			schedule = query.get_values()
		access_manager.disconnect(conn_name)
		return True, self.__to_json_schedule(schedule, query.get_column_names())

    		

	def __query_staff_data_from_db(self, login, passw):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = \
			"""SELECT a.login, a.access_level, s.*, p.*, ps.* 
				FROM staff s LEFT JOIN access a ON s.staff_id=a.employee 
					JOIN position p ON position=p.pos_id 
					JOIN passports ps ON s.passport=ps.pass_id 
						WHERE a.login='{}' AND a.password='{}';""".format(login, passw)
		query = DBQuery(conn, str_query)
		if not query.execQuery():
			return False, None
		else:
			result = query.get_values()

		if len(result) == 0:
			return False, None

		access_manager.disconnect(conn_name)
		return True, self.__to_json_staff_schedule(result, query.get_column_names())