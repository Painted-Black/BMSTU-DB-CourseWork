from .abstract_handler import AbstractHandler
from .utils import *

from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker

import json
import uuid

class AnimalUpsertHandler(AbstractHandler):
	def request(self, req, res):
		key = str(req.headers.get("Authorization"))
		type = str(req.headers.get("request-type"))
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

		status : bool
		data = json.loads(req.data)
		if type == 'put':
			status = self.__queryUpdateDb(data)
		else:
			status, out_index = self.__queryInsertDb(data, req.args.get("owner", default=None, type=None))
			data = {"anim_id": out_index}
			res.data = json.dumps(data)

		if not status:
			res.status_code=500
			return

		res.status_code=201

	def __queryInsertDb(self, data : dict, owner : int):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		query = DBQuery(conn)
		chip = data["chip_id"]


		query.begin_transaction()
		contract = data["contract"]
		chip = data["chip_id"]

		last_update_str=contract['last_update_date']
		if len(last_update_str) == 0:
			last_update_str='NULL'
		else:
			last_update_str="'{}'::date".format(last_update_str)

		str_query = '''INSERT INTO contract (code, conclusion_date, last_update_date, owner, valid_until) VALUES('{code}', '{conclusion_date}'::date,
			  {last_update_date}, '{owner}', '{valid_until}'::date) RETURNING contr_id;'''.format(
				  code=contract['code'], conclusion_date=contract['conclusion_date'], 
				  last_update_date=last_update_str, valid_until=contract['valid_until'],
				  owner=owner
			)

		contr_id : int
		if not query.exec_query(str_query):
			query.rollback_transaction()
			print(query.get_error())
			return False
		else:
			contr_id = query.get_values()[0][0]

		str_query = '''INSERT INTO microchips (chip_num, impl_date, country, location) 
						  VALUES('{chip_num}', '{impl_date}'::date, '{country}', '{location}') RETURNING chip_id;'''\
							  .format(chip_num=chip["chip_num"], impl_date=chip["impl_date"], country=chip["country"], location=chip["location"])

		chip_id : int
		if not query.exec_query(str_query):
			query.rollback_transaction()
			print(query.get_error())
			return False
		else:
			chip_id = query.get_values()[0][0]

		str_query = '''INSERT INTO animals_medical_records (name, breed, species, sex, castrated, birth, other_data, 
					      color, special_signs, registr_date, chip_id, contract, rel_path_to_photo) 
							VALUES ('{name}', '{breed}', '{species}', '{sex}', '{castrated}', '{birth}'::date, '{other}', '{color}', '{special_signs}', 
							'{registr_date}'::date, {chip_id}, {contract}, '{rel_path_to_photo}') RETURNING anim_id;'''\
								.format(name=data["name"], breed=data["breed"], species=data["species"], 
									sex=data["sex"], castrated=data["castrated"], birth=data["birth"], 
									other=data["other_data"], color=data["color"], special_signs=data["special_signs"], 
									registr_date=data["registr_date"], contract=contr_id, 
									chip_id=chip_id, rel_path_to_photo=data["rel_path_to_photo"])

		anim_id : int
		if not query.exec_query(str_query):
			query.rollback_transaction()
			print(query.get_error())
			return False, 0
		else:
			anim_id = query.get_values()[0][0]

		query.commit_transaction()
		access_manager.disconnect(conn_name)
		return True, anim_id

	def __queryUpdateDb(self, data : dict):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		query = DBQuery(conn)
		chip = data["chip_id"]


		query.begin_transaction()
		contract = data["contract"]
		chip = data["chip_id"]

		str_queries = []

		last_update_str=contract['last_update_date']
		if len(last_update_str) == 0:
			last_update_str='NULL'
		else:
			last_update_str="'{}'::date".format(last_update_str)


		str_queries.append('''UPDATE animals_medical_records 
						    SET name='{name}',
						      breed='{breed}',species='{species}', sex='{sex}', castrated='{castrated}', birth='{birth}'::date,
						  	  other_data='{other}', color='{color}', special_signs='{special_signs}', 
							  registr_date='{registr_date}'::date, chip_id={chip_id}, contract={contract}, 
							  rel_path_to_photo='{rel_path_to_photo}' WHERE anim_id={anim_id};'''.format(
						anim_id=data["anim_id"], name=data["name"], breed=data["breed"], 
						species=data["species"], sex=data["sex"], castrated=data["castrated"],
						birth=data["birth"], other=data["other_data"], color=data["color"],
						special_signs=data["special_signs"], registr_date=data["registr_date"], contract=contract["contr_id"],
						chip_id=chip["chip_id"], rel_path_to_photo=data["rel_path_to_photo"]))

		str_queries.append('''UPDATE contract 
			SET code='{code}', conclusion_date='{conclusion_date}'::date,
			  last_update_date={last_update_date}, valid_until='{valid_until}'::date WHERE contr_id={contr_id};'''.format(
				  code=contract['code'], conclusion_date=contract['conclusion_date'], last_update_date=last_update_str, 
				  valid_until=contract['valid_until'], contr_id=contract['contr_id']
			  ))

		str_queries.append('''UPDATE microchips 
			SET chip_num='{chip_num}', impl_date='{impl_date}'::date,
			  country='{country}', location='{location}' WHERE chip_id={chip_id}'''.format(
				  chip_num=chip["chip_num"], impl_date=chip["impl_date"], country=chip["country"], location=chip["location"], chip_id=chip["chip_id"]
			  ))

		for str_query in str_queries:
			if not query.exec_query(str_query):
				query.rollback_transaction()
				print(query.get_error())
				return False

		query.commit_transaction()
		access_manager.disconnect(conn_name)
		return True