import pandas as pd
from inline_sql import sql, sql_val

casos = pd.read_csv('casos.csv')
depto = pd.read_csv('departamento.csv')
etario = pd.read_csv('grupoetario.csv')
provincia = pd.read_csv('provincia.csv')
evento = pd.read_csv('tipoevento.csv')

#%% A. Consultas sobre una tabla
'''a. Listar sólo los nombres de todos los departamentos que hay en la tabla
departamento (dejando los registros repetidos).'''

consultaSQL = """
               SELECT descripcion
               FROM depto;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

'''b. Listar sólo los nombres de todos los departamentos que hay en la tabla
departamento (eliminando los registros repetidos).'''

consultaSQL = """
               SELECT DISTINCT descripcion
               FROM depto;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

'''c. Listar sólo los códigos de departamento y sus nombres, de todos los
departamentos que hay en la tabla departamento.'''

consultaSQL = """
               SELECT DISTINCT id, descripcion
               FROM depto;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

'''d. Listar todas las columnas de la tabla departamento.'''

consultaSQL = """
               SELECT DISTINCT id, descripcion,id_provincia
               FROM depto;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

'''e. Listar los códigos de departamento y nombres de todos los departamentos
que hay en la tabla departamento. Utilizar los siguientes alias para las
columnas: codigo_depto y nombre_depto, respectivamente.'''

consultaSQL = """
               SELECT DISTINCT id AS codigo_depto, descripcion AS nombre_depto
               FROM depto;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

'''f. Listar los registros de la tabla departamento cuyo código de provincia es
igual a 54'''

consultaSQL = """
               SELECT DISTINCT id, descripcion,id_provincia
               FROM depto
               WHERE id_provincia=54;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

'''g. Listar los registros de la tabla departamento cuyo código de provincia es
igual a 22, 78 u 86.'''

consultaSQL = """
               SELECT DISTINCT id, descripcion,id_provincia
               FROM depto
               WHERE id_provincia=22 OR id_provincia=78 OR id_provincia=86;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

'''h. Listar los registros de la tabla departamento cuyos códigos de provincia se
encuentren entre el 50 y el 59 (ambos valores inclusive).'''

consultaSQL = """
               SELECT DISTINCT id, descripcion,id_provincia
               FROM depto
               WHERE id_provincia>=50 AND id_provincia<=59;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

#%%B. Consultas multitabla (INNER JOIN)
'''a. Devolver una lista con los código y nombres de departamentos, asociados al
nombre de la provincia al que pertenecen.'''

depto_prov =sql^ """
               SELECT p.descripcion AS Provincia, d.id AS ID_Departamento, d.descripcion AS Departamento
               FROM depto AS d
               INNER JOIN provincia AS p
               ON d.id_provincia=p.id;
              """


print(depto_prov,'\n')

'''b. Devolver una lista con los código y nombres de departamentos, asociados al
nombre de la provincia al que pertenecen.'''
#igual al a -_-
'''c. Devolver los casos registrados en la provincia de “Chaco”.'''

consultaSQL = """
               SELECT DISTINCT c.*
               FROM casos AS c
               INNER JOIN depto_prov AS dp
               ON dp.ID_Departamento = c.id_depto AND dp.Provincia = 'Chaco';
              """
dfres = sql^ consultaSQL

print(dfres,'\n')
    
'''d. Devolver aquellos casos de la provincia de “Buenos Aires” cuyo campo
cantidad supere los 10 casos.'''

consultaSQL = """
               SELECT DISTINCT c.*
               FROM casos AS c
               INNER JOIN depto_prov AS dp
               ON dp.ID_Departamento = c.id_depto AND dp.Provincia = 'Buenos Aires' AND c.cantidad>10;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

#%%C. Consultas multitabla (OUTER JOIN)
'''a. Devolver un listado con los nombres de los departamentos que no tienen
ningún caso asociado.'''

consultaSQL = """
                SELECT DISTINCT descripcion AS Depto
                FROM depto 
                LEFT OUTER JOIN casos
                ON id_depto = depto.id
                WHERE cantidad IS NULL;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

'''b. Devolver un listado con los tipos de evento que no tienen ningún caso
asociado.'''

consultaSQL = """
                SELECT DISTINCT descripcion AS Evento
                FROM evento 
                LEFT OUTER JOIN casos
                ON id_tipoevento = evento.id
                WHERE cantidad IS NULL;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

#%%D. Consultas resumen
'''a. Calcular la cantidad total de casos que hay en la tabla casos.'''

consultaSQL = """
                SELECT count(*) AS Cantidad_de_casos
                   FROM casos;
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

'''b. Calcular la cantidad total de casos que hay en la tabla casos para cada año y
cada tipo de caso. Presentar la información de la siguiente manera:
descripción del tipo de caso, año y cantidad. Ordenarlo por tipo de caso
(ascendente) y año (ascendente).'''

consultaSQL = """
                SELECT evento.descripcion AS tipo_de_caso ,anio AS año, count(*) AS Cantidad
                FROM casos
                INNER JOIN evento
                ON id_tipoevento = evento.id
                GROUP BY anio,evento.descripcion
                ORDER BY evento.descripcion,anio;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')
'''c. Misma consulta que el ítem anterior, pero sólo para el año 2019.'''
consultaSQL = """
                SELECT evento.descripcion AS tipo_de_caso ,anio AS año, count(*) AS Cantidad
                FROM casos
                INNER JOIN evento
                ON id_tipoevento = evento.id AND anio=2019
                GROUP BY evento.descripcion,anio
                ORDER BY evento.descripcion,anio;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''d. Calcular la cantidad total de departamentos que hay por provincia. Presentar
la información ordenada por código de provincia.'''

consultaSQL = """
                SELECT id_provincia ,p.descripcion as Provincia,cantidad
                FROM provincia as p
                INNER JOIN (SELECT id_provincia , count(*) AS Cantidad
                            FROM depto 
                            GROUP BY id_provincia)
                ON id_provincia = p.id
                ORDER BY p.id
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''e. Listar los departamentos con menos cantidad de casos en el año 2019.'''

consultaSQL = """
                SELECT depto.descripcion AS depto2019 , count(*) AS Cantidad
                FROM casos
                INNER JOIN depto
                ON id_depto = depto.id AND anio=2019
                GROUP BY depto.descripcion
                ORDER BY cantidad,depto.descripcion;
                
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''f. Listar los departamentos con más cantidad de casos en el año 2020.'''

consultaSQL = """
                SELECT depto.descripcion AS depto2019 , count(*) AS Cantidad
                FROM casos
                INNER JOIN depto
                ON id_depto = depto.id AND anio=2020
                GROUP BY depto.descripcion
                ORDER BY cantidad DESC ,depto.descripcion;
                
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''g. Listar el promedio de cantidad de casos por provincia y año.'''

consultaSQL = """
                SELECT Provincia,anio  , AVG(Cantidad) AS PromedioCasos
                FROM casos
                INNER JOIN depto_prov
                ON id_depto = ID_Departamento
                GROUP BY Provincia,anio
                ORDER BY Provincia,anio DESC;
                
              """
dfres = sql^ consultaSQL

print(dfres,'\n')

'''h. Listar, para cada provincia y año, cuáles fueron los departamentos que más
cantidad de casos tuvieron.'''

dpc = sql^"""
          SELECT casos.*,provincia,departamento
          FROM casos
          INNER JOIN depto_prov
          ON id_depto = ID_Departamento;
          """

maxCasos =sql^ """
                SELECT Provincia,anio  , MAX(Cantidad) AS MAXCasos
                FROM dpc
                GROUP BY Provincia,anio
                ORDER BY Provincia,anio DESC;
              """
consultaSQL = """
                SELECT m.Provincia,m.anio , departamento , MAXCasos
                FROM dpc
                INNER JOIN maxCasos AS m
                ON dpc.Provincia=m.Provincia AND dpc.anio=m.anio AND cantidad=MAXCasos
                ORDER BY MAXCasos DESC;
                
              """              
    
dfres = sql^ consultaSQL

print(dfres,'\n')

'''i. Mostrar la cantidad de casos total, máxima, mínima y promedio que tuvo la
provincia de Buenos Aires en el año 2019.'''

consultaSQL = """
                SELECT MAX(Cantidad) AS MAX, MIN(Cantidad) AS MIN, AVG(cantidad) AS PROM
                FROM dpc
                WHERE provincia = 'Buenos Aires' AND anio = 2019;
              """              
    
dfres = sql^ consultaSQL

print('Casos en Buenos Aires 2019: \n',dfres,'\n')

'''j. Misma consulta que el ítem anterior, pero sólo para aquellos casos en que la
cantidad total es mayor a 1000 casos.'''

casosTot=sql^ """
                SELECT Provincia,anio  , SUM(Cantidad) AS CasosTot
                FROM dpc
                GROUP BY Provincia,anio
                ORDER BY casosTot DESC;
              """
print(casosTot)

consultaSQL = """
                SELECT ct.provincia, MAX(Cantidad) AS MAX, MIN(Cantidad) AS MIN, AVG(cantidad) AS PROM
                FROM dpc
                INNER JOIN casosTot AS ct
                ON ct.provincia = dpc.provincia  AND ct.anio = 2019 AND casosTot>1000
                GROUP BY ct.provincia
                ORDER BY max DESC;
              """              
    
dfres = sql^ consultaSQL

print('Casos en Buenos Aires 2019: \n',dfres,'\n')

'''k. Listar los nombres de departamento (y nombre de provincia) que tienen
mediciones tanto para el año 2019 como para el año 2020. Para cada uno de
ellos devolver la cantidad de casos promedio. Ordenar por nombre de
provincia (ascendente) y luego por nombre de departamento (ascendente).'''


dosA=sql^ """
                SELECT a.departamento AS depto
                FROM dpc AS a
                WHERE a.anio=2019
                INTERSECT
                SELECT b.departamento
                FROM dpc AS b
                WHERE b.anio=2020;
              """
print(dosA)
consultaSQL = """
                SELECT provincia,departamento, AVG(cantidad) AS PROMcasos
                FROM dpc
                INNER JOIN dosA 
                ON departamento = depto
                GROUP BY provincia,departamento
                ORDER BY provincia,departamento;
              """              
    
dfres = sql^ consultaSQL
print(dfres,'\n')

'''l. Devolver una tabla que tenga los siguientes campos: descripción de tipo de
evento, id_depto, nombre de departamento, id_provincia, nombre de
provincia, total de casos 2019, total de casos 2020'''

dpce = sql^"""
          SELECT dpc.* , descripcion as Evento
          FROM dpc
          INNER JOIN evento
          ON id_tipoevento = evento.id;
          """
info =sql^ """
                SELECT dpce.id,evento ,id_depto, departamento, provincia.id AS id_provincia, provincia
                FROM dpce
                INNER JOIN provincia 
                ON descripcion = provincia;
              """              

info2019 =sql^ """
                SELECT info.*,cantidad AS Casos2019
                FROM info 
                LEFT OUTER JOIN casos
                ON info.id=casos.id AND anio = 2019;
              """ 
info2020 =sql^ """
                SELECT info2019.*,cantidad AS Casos2020
                FROM info2019 
                LEFT OUTER JOIN casos
                ON info2019.id=casos.id AND anio = 2020;
              """
consultaSQL = """
                SELECT evento ,id_depto, departamento, id_provincia, provincia,SUM(Casos2019) AS Casos2019, SUM(Casos2020) AS Casos2020
                FROM info2020 
                GROUP BY evento ,id_depto, departamento, id_provincia, provincia
                ORDER BY Casos2019 DESC,Casos2020 DESC;
              """    
dfres = sql^ consultaSQL
print(dfres,'\n')

#%%E. Subconsultas (ALL, ANY)
'''a. Devolver el departamento que tuvo la mayor cantidad de casos sin hacer uso
de MAX, ORDER BY ni LIMIT.'''
casosXdepto = sql^ """
                SELECT departamento, SUM(cantidad) AS cantMax
                FROM dpc
                GROUP BY departamento;
              """ 
consultaSQL = """
                SELECT c1.departamento
                FROM casosXdepto AS c1
                WHERE c1.cantMax >= ALL(
                                    SELECT c2.cantMax
                                    FROM casosXdepto AS c2);
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''b. Devolver los tipo de evento que tienen casos asociados. (Utilizando ALL o ANY).'''
consultaSQL = """
                SELECT e.descripcion AS evento
                FROM evento AS e
                WHERE e.id = ANY(
                        SELECT id_tipoevento
                        FROM casos AS c);
              """
dfres = sql^ consultaSQL
print(dfres,'\n')  
    
#%%F. Subconsultas (IN, NOT IN)
'''a. Devolver los tipo de evento que tienen casos asociados (Utilizando IN, NOT IN).'''

consultaSQL = """
                SELECT e.descripcion AS evento
                FROM evento AS e
                WHERE e.id IN(
                        SELECT id_tipoevento
                        FROM casos AS c);
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''b. Devolver los tipo de evento que NO tienen casos asociados (Utilizando IN, NOT IN).'''

consultaSQL = """
                SELECT e.descripcion AS evento
                FROM evento AS e
                WHERE e.id NOT IN(
                        SELECT id_tipoevento
                        FROM casos AS c);
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

#%%G. Subconsultas (EXISTS, NOT EXISTS)
'''a. Devolver los tipo de evento que tienen casos asociados (Utilizando EXISTS, NOT EXISTS).'''

consultaSQL = """
                SELECT e.descripcion AS evento
                FROM evento AS e
                WHERE EXISTS(
                        SELECT c.id_tipoevento
                        FROM casos AS c
                        WHERE c.id_tipoevento=e.id );
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''b. Devolver los tipo de evento que NO tienen casos asociados (Utilizando IN, NOT IN).'''

consultaSQL = """
                SELECT e.descripcion AS evento
                FROM evento AS e
                WHERE NOT EXISTS(
                        SELECT c.id_tipoevento
                        FROM casos AS c
                        WHERE c.id_tipoevento=e.id );
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

#%%H. Subconsultas correlacionadas
'''a. Listar las provincias que tienen una cantidad total de casos mayor al
promedio de casos del país. Hacer el listado agrupado por año.'''
consultaSQL = """
                SELECT provincia,anio AS Año
                FROM casosTot AS ct
                WHERE casosTot >(
                        SELECT AVG(c.cantidad)
                        FROM casos AS c
                        WHERE c.anio=ct.anio
                        GROUP BY c.anio)
                ORDER BY anio,provincia;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')
'''b. Por cada año, listar las provincias que tuvieron una cantidad total de casos
mayor a la cantidad total de casos que la provincia de Corrientes.'''
consultaSQL = """
                SELECT ct1.provincia,ct1.anio AS Año
                FROM casosTot AS ct1
                WHERE casosTot > (
                        SELECT CasosTot
                        FROM casosTot AS ct2
                        WHERE ct2.anio=ct1.anio AND ct2.provincia='Corrientes')
                ORDER BY anio,casosTot DESC;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')
#%%I. Más consultas sobre una tabla
'''a. Listar los códigos de departamento y sus nombres, ordenados por estos
últimos (sus nombres) de manera descendentes (de la Z a la A). En caso de
empate, desempatar por código de departamento de manera ascendente.'''

consultaSQL = """
                SELECT id, descripcion AS departamento
                FROM depto
                ORDER BY descripcion DESC ,id;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''b. Listar los registros de la tabla provincia cuyos nombres comiencen con la letra M.'''

consultaSQL = """
                SELECT descripcion AS Provincia
                FROM provincia
                WHERE descripcion LIKE 'M%'
                ORDER BY descripcion;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''c. Listar los registros de la tabla provincia cuyos nombres comiencen con la
letra S y su quinta letra sea una letra A.'''

consultaSQL = """
                SELECT descripcion AS Provincia
                FROM provincia
                WHERE descripcion LIKE 'S___a%'
                ORDER BY descripcion;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''d. Listar los registros de la tabla provincia cuyos nombres terminan con la letra A.'''

consultaSQL = """
                SELECT descripcion AS Provincia
                FROM provincia
                WHERE descripcion LIKE '%a'
                ORDER BY descripcion;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''e. Listar los registros de la tabla provincia cuyos nombres tengan
exactamente 5 letras.'''

consultaSQL = """
                SELECT descripcion AS Provincia
                FROM provincia
                WHERE descripcion LIKE '_____'
                ORDER BY descripcion;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''f. Listar los registros de la tabla provincia cuyos nombres tengan ”do” en
alguna parte de su nombre.'''

consultaSQL = """
                SELECT descripcion AS Provincia
                FROM provincia
                WHERE descripcion LIKE '%do%'
                ORDER BY descripcion;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''g. Listar los registros de la tabla provincia cuyos nombres tengan ”do” en
alguna parte de su nombre y su código sea menor a 30.'''

consultaSQL = """
                SELECT descripcion AS Provincia
                FROM provincia
                WHERE descripcion LIKE '%do%' AND id<30
                ORDER BY descripcion;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''h. Listar los registros de la tabla departamento cuyos nombres tengan ”san”
en alguna parte de su nombre. Listar sólo id y descripcion. Utilizar los
siguientes alias para las columnas: codigo_depto y nombre_depto,
respectivamente. El resultado debe estar ordenado por sus nombres de
manera descendentes (de la Z a la A).'''

consultaSQL = """
                SELECT id AS codigo_depto, descripcion AS nombre_depto
                FROM depto
                WHERE descripcion LIKE '%San%'
                ORDER BY descripcion DESC;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''i. Devolver aquellos casos de las provincias cuyo nombre terminen con la letra
a y el campo cantidad supere 10. Mostrar: nombre de provincia, nombre de
departamento, año, semana epidemiológica, descripción de grupo etario y
cantidad. Ordenar el resultado por la cantidad (descendente), luego por el
nombre de la provincia (ascendente), nombre del departamento
(ascendente), año (ascendente) y la descripción del grupo etario
(ascendente).'''

consultaSQL = """
                SELECT provincia,departamento,anio AS año,semana_epidemiologica,e.descripcion AS GrupoEtario,cantidad
                FROM dpc
                INNER JOIN etario AS e
                ON e.id=id_grupoetario AND provincia LIKE '%a%' AND cantidad > 10
                ORDER BY cantidad DESC,provincia,departamento,anio,e.descripcion;
              """
ge = sql^ consultaSQL
print(ge,'\n')

'''j. Ídem anterior, pero devolver sólo aquellas tuplas que tienen el máximo en el
campo cantidad.'''

consultaSQL = """
                SELECT  m.provincia,departamento,año,semana_epidemiologica,GrupoEtario,MAXCasos
                FROM ge
                INNER JOIN maxCasos AS m
                ON m.provincia=ge.provincia AND año=anio AND MAXCasos=cantidad;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')


#%%J. Reemplazos
'''a. Listar los id y descripción de los departamentos. Estos últimos sin tildes y en
orden alfabético.'''

consultaSQL = """
                SELECT DISTINCT id, REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(descripcion,'á','a'),'é','e'),'í','i'),'ó','o'),'ú','u') AS Departamento
                FROM depto
                ORDER BY descripcion;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')

'''b. Listar los nombres de provincia en mayúscula, sin tildes y en orden
alfabético.'''

consultaSQL = """
                SELECT DISTINCT  UPPER(REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(descripcion,'á','a'),'é','e'),'í','i'),'ó','o'),'ú','u')) AS PROVINCIA
                FROM provincia
                ORDER BY descripcion;
              """
dfres = sql^ consultaSQL
print(dfres,'\n')
