from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
import json
import uuid


class AllVisitsHandler(AbstractHandler):
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
		str_query = '''SELECT v.vis_id, v.visit_date, p.surname, p.name, p.patronymic, a.name, a.species
			FROM visits v JOIN staff s ON v.doctor=s.staff_id 
			JOIN passports p ON s.passport=p.pass_id
			JOIN animals_medical_records a ON v.animal=a.anim_id;'''
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
			vis = {}
			staff = {}
			passp = {}
			anim = {}
			for j in range(0, 2):
				vis[column_names[j]] = str(result[i][j])
			
			for j in range(2, 5):
				passp[column_names[j]] = str(result[i][j])

			for j in range(5, 7):
				anim[column_names[j]] = str(result[i][j])
			
			staff['passport'] = passp
			vis['doctor'] = staff
			vis['animal'] = anim

			res_json.append(vis)

		return res_json
