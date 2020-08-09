from database.dbconn import DBConn
from database.dbquery import DBQuery

class DBAccessManager(object):
	def __init__(self):
		self.connections = {}

	def init(self, conn_info, conn_count):
		self.conn_info = conn_info
		self.count = int(conn_count)

	def connect(self, c_name):
		new_conn = DBConn(self.conn_info)
		is_ok = False
		i = 0
		while i < self.count and not is_ok:
			is_ok = new_conn.try_connect()
			i += 1
		if not is_ok:
			return None
		self.connections[c_name] = new_conn
		return self.connections[c_name]
	
	def disconnect(self, c_name):
		self.connections.pop(c_name)

access_manager = DBAccessManager()
