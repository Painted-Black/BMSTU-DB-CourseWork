class DBQuery(object):
	def __init__(self, dbconn, query=""):
		self.query_buffer=query
		self.conn = dbconn

	#def prepare(self, query):
		#self.query_buffer = query

	#def add_bind_value(self, arg, val):
		# not impl
		#pass

	def get_colunm_names(self):
		l = [ i[0] for i in self.column_names]
		return l

	def execQuery(self, query = ""):
		if query != "":
			self.query_buffer=query

		try:
			cursor = self.conn.conn.cursor()
			cursor.execute(self.query_buffer)
			self.values = cursor.fetchall()
			self.column_names = cursor.description
		except:
			return False
		finally:
			cursor.close()
			del cursor
		
		return True

	def get_values(self):
		return self.values