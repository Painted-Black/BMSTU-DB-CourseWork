from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
import json
import uuid


class VisitFullInfo(AbstractHandler):
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

		_id = req.args.get("id", default=None, type=None)
		status, data = self.__queryDb(_id)
		if not status:
			res.status_code=500
			return

		res.data = json.dumps(data)
		res.status_code=200
	
	def __queryDb(self, vis_id):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = '''SELECT vis.*, stat.*, anim.anim_id, anim.name, anim.species, s.staff_id, 
			pos.title, pass.name, pass.surname, pass.patronymic
			FROM visits vis JOIN animals_medical_records anim ON vis.animal=anim.anim_id
			JOIN staff s ON vis.doctor=s.staff_id
			JOIN position pos ON s.position=pos.pos_id
			JOIN passports pass ON s.passport=pass.pass_id
			JOIN animal_states stat ON vis.cur_state=stat.state_id
			WHERE vis.vis_id = {i};'''.format(i=vis_id)
		query = DBQuery(conn)
		if not query.exec_query(str_query):
			print(query.get_error())
			return False, ""
		else:
			result = query.get_values()

		access_manager.disconnect(conn_name)
		return True, self.__construct_json(result, query.get_column_names())

	def __construct_json(self, result : list, column_names : list):
		result = result[0]
		print(result)
		print(column_names)
		#for i in range(len(result)):
		vis = {}
		staff = {}
		pos = {}
		state = {}
		anim = {}
		passp = {}

		vis[column_names[0]] = str(result[0])

		for j in range(3, 6):
			vis[column_names[j]] = str(result[j])

		for j in range(7, 12):
			vis[column_names[j]] = str(result[j])
			
		for j in range(12, 20):
			state[column_names[j]] = str(result[j])

		for j in range(20, 23):
			anim[column_names[j]] = str(result[j])

		staff[column_names[23]] = str(result[23])

		pos[column_names[24]] = str(result[24])

		for j in range(25, 28):
			passp[column_names[j]] = str(result[j])
			
		staff['passport'] = passp
		staff['position'] = pos
		vis['doctor'] = staff
		vis['animal'] = anim
		vis['cur_state'] = state

		return vis
