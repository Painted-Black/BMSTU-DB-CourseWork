def to_json(rows : list, column_names : list):
	arr = []
	l = len(column_names)
	for i in rows:
		d = {}
		for j in range (l):
			d[column_names[j]] = str(i[j])
		arr.append(d)
	return arr