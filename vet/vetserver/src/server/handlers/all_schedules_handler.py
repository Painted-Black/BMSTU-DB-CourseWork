from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
import json
import uuid


class AllSchedulesHandler(AbstractHandler):
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
		str_query = '''SELECT sch.shed_id, sch.day_of_week, sch.start, sch."end", sch.cabinet, st.staff_id, pos.pos_id, pos.title, pass.pass_id, pass.surname, pass.name, pass.patronymic 
		FROM schedule sch JOIN staff st ON sch.employee_id=st.staff_id
		JOIN position pos ON st.position=pos.pos_id
		JOIN passports pass ON st.passport=pass.pass_id;'''
		query = DBQuery(conn)
		if not query.exec_query(str_query):
			return False, ""
		else:
			result = query.get_values()

		access_manager.disconnect(conn_name)
		return True, self.__construct_json(result, query.get_column_names())

	def __construct_json(self, result : list, column_names : list):
		res_json = []
		print(result)
		print(column_names)
		prev_st_id = -1
		sched_list = []
		for i in range(len(result)):
			st_id = result[i][5]
			sched = {}
			if (prev_st_id != st_id):
				position = {}
				staff = {}
				passport = {}

				for j in range(6, 8):
					position[column_names[j]] = str(result[i][j])
			
				for j in range(8, 12):
					passport[column_names[j]] = str(result[i][j])
				
				staff['staff_id'] = str(result[i][5])
				staff['passport'] = passport
				staff['position'] = position

			for j in range(0, 5):
				sched[column_names[j]] = str(result[i][j])
			sched_list.append(sched)
			
			if prev_st_id != st_id and i != 0:
				s = {}
				s['schedule'] = sched_list
				s['staff'] = staff
				res_json.append(s)
				sched_list = []
		a = 0
		return res_json
