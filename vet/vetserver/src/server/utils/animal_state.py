class AnimalState():
	def __init__(self):
		self.__state_id = None
		self.__general = None
		self.__pulse = None
		self.__weight = None
		self.__ap = None
		self.__temperature = None
		self.__cfr = None
		self.__resp_rate = None
	
	def deserialize(self, json):
		self.__general = json['general']
		self.__pulse = json['pulse']
		self.__weight = json['weight']
		self.__ap = json['ap']
		self.__temperature = json['temperature']
		self.__cfr = json['cfr']
		self.__resp_rate = json['resp_rate']

	def get_state_id(self):
		return self.__state_id
	
	def get_general(self):
		return self.__general

	def get_pulse(self):
		return self.__pulse

	def get_weight(self, weight):
		return self.__weight

	def get_ap(self):
		return self.__ap
	
	def get_temperature(self):
		return self.__temperature

	def get_cfr(self):
		return self.__cfr

	def get_resp_rate(self):
		return self.__resp_rate
	
	def set_state_id(self, id : int):
		self.__state_id = id

	def set_general(self, general : str):
		self.__general = general

	def set_pulse(self, pulse : int):
		self.__pulse = pulse

	def set_weight(self, weight : float):
		self.__weight = weight

	def set_ap(self, ap : str):
		self.__ap = ap
	
	def set_temperature(self, temperature : float):
		self.__temperature = temperature

	def set_cfr(self, cfr : int):
		self.__cfr = cfr

	def set_resp_rate(self, resp_rate : int):
		self.__resp_rate = resp_rate

	def is_valid(self):
		try:
			res = ( self.__state_id >= 0 and (self.__general == "middle" or self.__general == "good" or self.__general == "bad") and self.__pulse > 0 and self.__weight > 0 and self.__cfr > 0 and self.__resp_rate > 0)
			return res
		except TypeError:
			return False