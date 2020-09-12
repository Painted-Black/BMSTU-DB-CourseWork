from .dbconn import DBConn

class DBQuery(object):
	def __init__(self, dbconn : DBConn):
		self.conn = dbconn
		self.is_transaction=False
		self.cursor = dbconn.new_query(self)

	def __del__(self):
		if self.is_transaction:
			print("Transaction was not commit. Rollback")
			self.rollback_transaction()

		self.cursor.close()
		del self.cursor

	def get_error(self):
		return self.str_error

	def get_column_names(self):
		l = [ i[0] for i in self.cursor.description]
		return l

	def begin_transaction(self):
		self.is_transaction=True

	def rollback_transaction(self):
		self.cursor.rollback()

	def commit_transaction(self):
		if self.is_transaction:
			self.cursor.commit()
		self.is_transaction=False


	def exec_query(self, query : str):
		print("Query:\n{}".format(query))
		try:
			self.cursor.execute(query)
			if self.is_transaction == False:
				self.cursor.commit()
		except Exception as e:
			self.str_error=e
			return False
		return True

	def get_values(self):
		return self.cursor.fetchall()