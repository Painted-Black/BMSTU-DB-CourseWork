class DBQuery(object):
	def __init__(self, dbconn, query=""):
		self.query_buffer=query
		self.conn = dbconn

	#def prepare(self, query):
		#self.query_buffer = query

	#def add_bind_value(self, arg, val):
		# not impl
		#pass

	def get_error(self):
		return self.str_error

	def get_column_names(self):
		l = [ i[0] for i in self.column_names]
		return l

	def execQuery(self, query = ""):
		print("QUERY:")
		print(query)
		if query != "":
			self.query_buffer=query
		try:
			cursor = self.conn.conn.cursor()
			cursor.execute(self.query_buffer)
			cursor.commit()
			try:
				self.values = cursor.fetchall()
			except:
				pass
			self.column_names = cursor.description
		except Exception as e:
			self.str_error=e
			return False
		finally:
			cursor.close()
			del cursor
		
		return True

	def get_values(self):
		return self.values