from .dbconn import DBConn

class DBQuery(object):
	def __init__(self, dbconn : DBConn, query=""):
		self.query_buffer=query
		self.conn = dbconn
		self.is_transaction=False
		self.cursor = dbconn.new_query(self)

	def __del__(self):
		self.cursor.close()
		del self.cursor

	def get_error(self):
		return self.str_error

	def get_column_names(self):
		l = [ i[0] for i in self.cursor.description]
		return l

	def begin_transaction(self):
		self.is_transaction=True

	def commit_transaction(self):
		if self.is_transaction:
			self.cursor.commit()


	def execQuery(self, query = ""):
		print("QUERY:")
		print(query)
		if query != "":
			self.query_buffer=query
		try:
			self.cursor.execute(self.query_buffer)
			if self.is_transaction == False:
				self.cursor.commit()
		except Exception as e:
			self.str_error=e
			return False
		return True

	def get_values(self):
		return self.cursor.fetchall()