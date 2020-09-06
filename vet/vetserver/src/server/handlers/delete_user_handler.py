from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
import json
import uuid


class DeleteUserHandler(AbstractHandler):
	def request(self, req, res):
		res.content_type = "application/json"
		try:
			json_data = json.loads(req.data)
		except json.decoder.JSONDecodeError:
			res.status_code=403
			res.data = json.dumps({"error" : "Empty json"})
			return
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

		if not json_data.__contains__('acc_id'):
			res.status_code=403
			res.data = json.dumps({"error" : "Expected values was not received"})
			return

		status = self.__queryDb(json_data['acc_id'])
		if not status:
			res.status_code=500
			return

		res.status_code=204
	
	def __queryDb(self, acc_id : str):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = '''DELETE FROM access WHERE acc_id = {id}
		'''.format(id=acc_id)
		query = DBQuery(conn)
		if not query.exec_query(str_query):
			print(query.get_error())
			return False

		access_manager.disconnect(conn_name)
		return True