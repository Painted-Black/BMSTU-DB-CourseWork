class DBConnInfo(object):
	def __init__(self, driver="", server="", port="", db="", user="", password=""):
		self.driver=driver
		self.server=server
		self.port=port
		self.db=db
		self.username=user
		self.password=password

	def setDriver(self, driver):
		self.driver = driver

	def setServer(self, server):
		self.server = server

	def setPort(self, port):
		self.port = port

	def setDBname(self, db):
		self.db = db

	def setUser(self, user):
		self.username = user

	def setPassword(self, password):
		self.password = password

	def getDriver(self):
		return self.driver

	def getServer(self):
		return self.server

	def getPort(self):
		return self.port

	def getDBname(self):
		return self.db

	def getUser(self):
		return self.username

	def getPassword(self):
		return self.password