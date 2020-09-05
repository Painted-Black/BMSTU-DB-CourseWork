from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
import json
import uuid


class ShortStaffInfo(AbstractHandler):
	def request(self, req, res):
		res.content_type = "application/json"
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

		status, data = self.__queryDb()
		if not status:
			res.status_code=500
			return

		res.data = json.dumps(data)
		res.status_code=200
	
	def __queryDb(self):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = '''SELECT pas.name, pas.surname, pas.patronymic, pos.title, s.fire_date, s.employ_date 
		FROM staff s JOIN passports pas ON pas.pass_id=s.staff_id
    		JOIN position pos ON s.position=pos.pos_id
			WHERE s.staff_id NOT IN 
			(SELECT employee FROM access);
		'''
		query = DBQuery(conn, str_query)
		if not query.execQuery():
			return False, ""
		else:
			result = query.get_values()

		access_manager.disconnect(conn_name)
		return True, self.__construct_json(result, query.get_column_names())

	def __construct_json(self, result : list, column_names : list):
		res_json = []
		for i in range(len(result)):
			staff = {}
			passport = {}
			position = {}
			for j in range(0, 3):
				passport[column_names[j]] = str(result[i][j])
			
			position[column_names[3]] = result[i][3]

			for j in range(4, 6):
				staff[column_names[j]] = str(result[i][j])

			staff['passport'] = passport
			staff['position'] = position

			res_json.append(staff)
		return res_json
