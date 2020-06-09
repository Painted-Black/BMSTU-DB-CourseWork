import pyodbc

# conn_str = ';'.join([driver, server, port, db, user, pw])

# sudo apt install odbc-postgresql
class DBConn(object):
	def __init__(self, dbconn_info):
		self.conn_info=dbconn_info
		self.conn_state=False

	def try_connect(self):
		conn_str='DRIVER={driver};SERVER={server};PORT={port};DATABASE={db};UID={user};PWD={pwd}'.format(
			driver=self.conn_info.getDriver(),
			server=self.conn_info.getServer(),
			port=self.conn_info.getPort(),
			db=self.conn_info.getDBname(),
			user=self.conn_info.getUser(),
			pwd=self.conn_info.getPassword())
		try:
			self.conn = pyodbc.connect(conn_str)
		except:
			return False
		self.conn_state=True
		return True

	def is_connected(self):
		return self.conn_state
