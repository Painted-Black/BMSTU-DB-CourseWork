from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
import json
import uuid

class CurrentVisitsHandler(AbstractHandler):
	def request(self, req, res):
		res.content_type = "application/json"

		try:
			data = json.loads(req.data)
		except json.decoder.JSONDecodeError:
			res.status_code=403
			res.data = json.dumps({"error" : "Empty fields"})
			return

		key = str(req.headers.get("Authorization"))
		# Authorization: Explicit Key
		explicit_key="Explicit: "
		idx = key.find(explicit_key) 
		if idx == -1:
			res.status_code=401
			return

		#key = key[len(explicit_key):]
		#staff_id = valid_key_checker.get_owner(key)
		#if staff_id == -1:
		#	res.status_code=401
		#	return
        # TODO check

		if not data.__contains__('date'):
			res.status_code=403
			res.data = json.dumps({"error" : "Expected values was not received"})
			return
		status, data = self.__query_visits_from_db(data['date'])
		if not status:
			res.status_code=500
			return

		res.data = json.dumps(data)
		res.status_code=200

	def __query_visits_from_db(self, date : str):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = """SELECT a.name, a.species FROM visits v JOIN animals_medical_records a ON v.animal = a.anim_id WHERE v.next_visit = '{}';""".format(date)
		query = DBQuery(conn, str_query)
		if not query.execQuery(str_query):
			return False, ""
		else:
			result = query.get_values()

		access_manager.disconnect(conn_name)
		return True, self._to_json(result, query.get_column_names())