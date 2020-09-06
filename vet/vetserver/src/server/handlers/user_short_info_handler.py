from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
import json
import uuid

class UserShortInfoHandler(AbstractHandler):
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

		status, data = self.__queryDb()
		if not status:
			res.status_code=500
			return

		res.data = json.dumps(data)
		res.status_code=200

	def __queryDb(self):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = '''SELECT acc_id, login, password, surname, name,
		patronymic, access_level, title, employ_date, fire_date 
		FROM access a JOIN staff s ON a.employee=s.staff_id 
		JOIN position p ON s.position=p.pos_id 
		JOIN passports pas ON s.passport=pas.pass_id;
		'''
		query = DBQuery(conn)
		if not query.exec_query(str_query):
			return False, ""
		else:
			result = query.get_values()

		access_manager.disconnect(conn_name)
		return True, self.__construct_json(result, query.get_column_names())

	def __construct_json(self, result : list, column_names : list):
		res_json = []
		print(result, column_names)
		for i in range(len(result)):
			access = {}
			passport = {}
			position = {}
			staff = {}
			for j in range(3, 6):
				passport[column_names[j]] = str(result[i][j])
			
			for j in range(0, 2):
				access[column_names[j]] = str(result[i][j])
			
			access[column_names[2]] = result[i][2].decode('utf-8')

			access[column_names[6]] = str(result[i][6])
			position[column_names[7]] = str(result[i][7])

			for j in range(8, 10):
				staff[column_names[j]] = str(result[i][j])

			staff['position'] = position
			staff['passport'] = passport
			access['employee'] = staff
			
			res_json.append(access)
		
		return res_json
