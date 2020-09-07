from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
import json
import uuid


class FullStaffInfo(AbstractHandler):
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
		str_query = '''SELECT * FROM staff st
						JOIN position pos ON st.position=pos.pos_id
						JOIN passports pas ON st.passport=pas.pass_id;'''
		query = DBQuery(conn)
		if not query.exec_query(str_query):
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

			staff[column_names[0]] = str(result[i][0])

			for j in range(3, 6):
				staff[column_names[j]] = str(result[i][j])
			
			for j in range(6, 9):
				position[column_names[j]] = str(result[i][j])

			for j in range(9, 18):
				passport[column_names[j]] = str(result[i][j])

			position[column_names[3]] = result[i][3]

			staff['passport'] = passport
			staff['position'] = position

			res_json.append(staff)
		return res_json
