def create_tables(c, conn):
    c.execute('''CREATE TABLE a (edge real, id real)''')
    c.execute('''CREATE TABLE Id_First_Last (id real, first1 VARCHAR, last1 VARCHAR)''')
    conn.commit()


def drop_table(c, conn):
    c.execute('''DROP TABLE a''')
    c.execute('''DROP TABLE Id_First_Last''')
    conn.commit()


def database_commit(conn):
    conn.commit()


def get_all_sd_using_this(c, id):
    sql = 'select id from a where id=%s'
    val = (id)
    sql = sql % val
    try:
        result = c.execute(sql).fetchall()
        return result
        # return c.lastrowid
    except:
        print('Something we wrong: get_all_sd_using_this ')


def add_to_traffic_db(c, id, traffic):
    sql = 'INSERT INTO Id_Traffic (id, traffic) VALUES (%s,%s)'
    val = (int(id), int(traffic))
    sql = sql % val
    try:
        c.execute(sql)
        # return c.lastrowid
    except:
        print('Something we wrong: INSERT INTO Id_Traffic ')


def get_first_last_from_id(c, id):
    sql = 'select first1, last1 from Id_First_Last where id=%s'
    val = (id)
    sql = sql % val
    try:
        result = c.execute(sql).fetchall()
        return result
        # return c.lastrowid
    except:
        print('Something we wrong: get_first_last_from_id ')

def add_to_frist_last(c, id, first, last):
    sql = 'INSERT INTO Id_First_Last (id, first1, last1) VALUES (%s,%s,%s)'
    val = (int(id), '\'' + str(first[0]) + '_' + str(first[1]) + "\'", "\'" + str(last[0]) + '_' + str(last[1]) + "\'")
    sql = sql % val
    try:
        c.execute(sql)
        # return c.lastrowid
    except:
        print('Something we wrong: INSERT INTO Id_First_Last')

def add_to_a(c, v1, sd_id):
    sql = 'INSERT INTO a (edge, id) VALUES (%s,%s)'
    try:
        val = (int(v1), int(sd_id))
    except TypeError:
        print(v1)
        print(type(v1))
        print(sd_id)
        print(type(sd_id))
    sql = sql % val
    try:
        c.execute(sql)
        # return c.lastrowid
    except:
        print('Something we wrong: INSERT INTO Id_Traffic ')


