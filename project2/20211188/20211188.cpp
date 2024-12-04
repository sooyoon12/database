#include <cstdio>
#include <cstdlib>
#include "mysql.h"
#include <iostream>
#include <string>
#include <fstream>

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "0603";
const char* db = "dbs";
using namespace std;

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}
	else
	{
		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		int state = 0;

		// create table
		ifstream fc;
		fc.open("create.txt");
		string line;

		while (getline(fc, line)) {
			const char* qline = line.c_str();
			state = mysql_query(connection, qline);
		}
		fc.close();

		// insert
		ifstream fi;
		fi.open("insert.txt");

		while (getline(fi, line)) {
			const char* qline = line.c_str();
			state = mysql_query(connection, qline);
		}
		fi.close();
		string query;
		const char* cquery;
		while (true) {
			printf("------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE I\n");
			printf("\t2. TYPE II\n");
			printf("\t3. TYPE III\n");
			printf("\t4. TYPE IV\n");
			printf("\t5. TYPE V\n");
			printf("\t6. TYPE VI\n");
			printf("\t7. TYPE VII\n");
			printf("\t8. TYPE VIII\n");
			printf("\t0. QUIT\n");

			int type; cin >> type;
			if (type == 0) break;
			if (type == 1) {
				printf("---- TYPE I ----\n");
				printf("** Find address of homes for sale in the distinct mapo. **\n");
				query = "SELECT property_address ";
				query += "FROM property ";
				query += "WHERE property_address LIKE '%mapo-gu%'";
				const char* cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Query Error: %s\n", mysql_error(connection));
				}
				else {
					sql_result = mysql_store_result(connection);
					if (sql_result) {
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("property_address : %s\n", sql_row[0]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("No results found.\n");
					}
				}
				printf("\n");
				printf("----- Subtypes in TYPE I -----\n");
				printf("   1.  TYPE I-1.\n");
				int sub_num; cin >> sub_num;
				if (sub_num == 0) continue;
				if (sub_num == 1) {
					printf("---- TYPE I-1 ----\n");
					printf("** Find the costing between \ 1,000,000,000 and \1,500,000,000. **\n");
					query = "SELECT property_address ";
					query += "FROM property ";
					query += "WHERE property_address LIKE '%mapo-gu%' ";
					query += "AND property_price BETWEEN 1000000000 AND 1500000000";
					cquery = query.c_str();
					state = mysql_query(connection, cquery);
					if (state != 0) {
						printf("Query Error: %s\n", mysql_error(connection));
					}
					else {
						sql_result = mysql_store_result(connection);
						if (sql_result) {
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("property_address : %s\n", sql_row[0]);
							}
							mysql_free_result(sql_result);
						}
						else {
							printf("No results found.\n");
						}
					}
					printf("\n");
				}
			}
			if (type == 2) {
				printf("---- TYPE 2 ----\n");
				printf("** Find the address of homes for sale in the 8th school district. **\n");
				query = "SELECT property_address ";
				query += "FROM property ";
				query += "JOIN school_distance USING(school_distance_num) ";
				query += "WHERE school_distance_num=8";
				const char* cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Query Error: %s\n", mysql_error(connection));
				}
				else {
					sql_result = mysql_store_result(connection);
					if (sql_result) {
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("%s\n", sql_row[0]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("No results found.\n");
					}
				}
				printf("\n");
				printf("----- Subtypes in TYPE 2 -----\n");
				printf("   1.  TYPE 2-1.\n");
				int sub_num; cin >> sub_num;
				if (sub_num == 0) continue;
				if (sub_num == 1) {
					printf("---- TYPE 2-1 ----\n");
					printf("** Find properties with 4 or more bedrooms and 2 bathrooms **\n");
					query = "SELECT property_address ";
					query += "FROM property ";
					query += "JOIN school_distance USING(school_distance_num) ";
					query += "WHERE school_distance_num=8 ";
					query += "AND property_bedroom >= 4 ";
					query += "AND property_bathroom=2";
					cquery = query.c_str();
					state = mysql_query(connection, cquery);
					if (state != 0) {
						printf("Query Error: %s\n", mysql_error(connection));
					}
					else {
						sql_result = mysql_store_result(connection);
						if (sql_result) {
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("property_address : %s\n", sql_row[0]);
							}
							mysql_free_result(sql_result);
						}
						else {
							printf("No results found.\n");
						}
					}
					printf("\n");
				}
			}
			if (type == 3) {
				printf("---- TYPE III ----\n");
				printf("** Find the name of the agent who has sold the most properties in the year 2022 by total won value **\n");
				query = "SELECT a.agent_id, a.agent_name, SUM(rsp.sold_price) AS total_value_2022 ";
				query += "FROM contact ";
				query += "NATURAL JOIN recently_sold_properties rsp ";
				query += "JOIN agent a USING(agent_id) ";
				query += "WHERE YEAR(rsp.sold_date) = 2022 ";
				query += "GROUP BY a.agent_id, a.agent_name ";
				query += "ORDER BY total_value_2022 DESC ";
				query += "LIMIT 1";
				cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Query Error: %s\n", mysql_error(connection));
				}
				else {
					sql_result = mysql_store_result(connection);
					if (sql_result) {
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("agent_id : %s\nagent_name : %s\ntotal_value_2022 : %s\n", sql_row[0], sql_row[1], sql_row[2]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("No results found.\n");
					}
				}
				printf("\n");
				printf("----- Subtypes in TYPE 3 -----\n");
				printf("   1.  TYPE 3-1.\n");
				printf("   2.  TYPE 3-2.\n");
				int sub_num; cin >> sub_num;
				if (sub_num == 0) continue;
				if (sub_num == 1) {
					printf("---- TYPE 3-1 ----\n");
					printf("** Find the top k agents in the year 2023 by total won value. **\n");
					printf("Which k? :");
					int x; cin >> x;
					query = "WITH RankedAgents AS (";
					query += "SELECT a.agent_id, a.agent_name, SUM(rsp.sold_price) AS total_value_2023, ";
					query += "DENSE_RANK() OVER (ORDER BY SUM(rsp.sold_price) DESC) AS rank_value ";
					query += "FROM contact c JOIN agent a ON c.agent_id = a.agent_id ";
					query += "JOIN recently_sold_properties rsp ON c.seller_id = rsp.sold_id ";
					query += "WHERE YEAR(rsp.sold_date) = 2023 ";
					query += "GROUP BY a.agent_id, a.agent_name ";
					query += ") SELECT agent_id, agent_name, total_value_2023 ";
					query += "FROM RankedAgents ";
					query += "WHERE rank_value < " + to_string(x);
					cquery = query.c_str();
					state = mysql_query(connection, cquery);
					if (state != 0) {
						printf("Query Error: %s\n", mysql_error(connection));
					}
					else {
						sql_result = mysql_store_result(connection);
						if (sql_result) {
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("agent_id : %s\nagent_name : %s\ntotal_value_2023 : %s\n", sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
						else {
							printf("No results found.\n");
						}
					}
				}
				if (sub_num == 2) {
					printf("---- TYPE 3-2 ----\n");
					printf("** Find the bottom 10percent agents in the year 2021 by total won value. **\n");
					query = "WITH AgentSales2021 AS (";
					query += "SELECT a.agent_id, a.agent_name, SUM(rsp.sold_price) AS total_value_2021 ";
					query += "FROM contact ";
					query += "NATURAL JOIN recently_sold_properties rsp ";
					query += "JOIN agent a USING(agent_id) ";
					query += "WHERE YEAR(rsp.sold_date) = 2021 ";
					query += "GROUP BY a.agent_id, a.agent_name ";
					query += "), ";
					query += "AgentSalesCount AS (";
					query += "SELECT COUNT(*) AS total_agents FROM AgentSales2021 ";
					query += "), ";
					query += "Bottom10Percent AS (";
					query += "SELECT *, NTILE(10) OVER (ORDER BY total_value_2021 ASC) AS decile ";
					query += "FROM AgentSales2021 ";
					query += ") ";
					query += "SELECT agent_id, agent_name, total_value_2021 ";
					query += "FROM Bottom10Percent ";
					query += "WHERE decile = 1;";
					cquery = query.c_str();
					state = mysql_query(connection, cquery);
					if (state != 0) {
						printf("Query Error: %s\n", mysql_error(connection));
					}
					else {
						sql_result = mysql_store_result(connection);
						if (sql_result) {
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("agent_id : %s\nagent_name : %s\ntotal_value_2021 : %s\n", sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
						else {
							printf("No results found.\n");
						}
					}
					printf("\n");
				}
			}
			if (type == 4) {
				printf("---- TYPE IV ----\n");
				printf("** Compute the average selling price of 2022, average time the property was on the market. **\n");
				query = "SELECT a.agent_id, a.agent_name, ";
				query += "AVG(rsp.sold_price) AS avg_selling_price_2022, ";
				query += "AVG(DATEDIFF(rsp.sold_date, rsp.sold_resister_date)) AS avg_time_on_market ";
				query += "FROM recently_sold_properties rsp ";
				query += "JOIN contact c ON rsp.sold_id = c.contact_id ";
				query += "JOIN agent a ON c.agent_id = a.agent_id ";
				query += "WHERE YEAR(rsp.sold_date) = 2022 ";
				query += "GROUP BY a.agent_id, a.agent_name ";
				query += "LIMIT 0, 1000;";
				cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Query Error: %s\n", mysql_error(connection));
				}
				else {
					sql_result = mysql_store_result(connection);
					if (sql_result) {
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("agent_id : %s\nagent_name : %s\navg_selling_price_2022 : %s\navg_time_on_market : %s\n",
								sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("No results found.\n");
					}
				}
				printf("\n");
				printf("----- Subtypes in TYPE IV -----\n");
				printf("   1.  TYPE IV-1.\n");
				printf("   2.  TYPE IV-2.\n");
				int sub_num; cin >> sub_num;
				if (sub_num == 0) continue;
				if (sub_num == 1) {
					printf("---- TYPE IV-1 ----\n");
					printf("** Compute max selling price of properties sold in 2023 for each agent **\n");
					query = "SELECT a.agent_id, a.agent_name, ";
					query += "MAX(rsp.sold_price) AS max_selling_price_2023 ";
					query += "FROM recently_sold_properties rsp ";
					query += "JOIN contact c ON rsp.sold_id = c.contact_id ";
					query += "JOIN agent a ON c.agent_id = a.agent_id ";
					query += "WHERE YEAR(rsp.sold_date) = 2023 ";
					query += "GROUP BY a.agent_id, a.agent_name;";
					cquery = query.c_str();
					state = mysql_query(connection, cquery);
					if (state != 0) {
						printf("Query Error: %s\n", mysql_error(connection));
					}
					else {
						sql_result = mysql_store_result(connection);
						if (sql_result) {
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("agent_id : %s\nagent_name : %s\nmax_selling_price_2023 : %s\n", sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
						else {
							printf("No results found.\n");
						}
					}
					printf("\n");
				}
				if (sub_num == 2) {
					printf("---- TYPE IV-2 ----\n");
					printf("** Compute the longest time the property was on the market for each agent **\n");
					query = "SELECT a.agent_id, a.agent_name, ";
					query += "MAX(DATEDIFF(rsp.sold_date, rsp.sold_resister_date)) AS longest_time_on_market ";
					query += "FROM recently_sold_properties rsp ";
					query += "JOIN contact c ON rsp.sold_id = c.contact_id ";
					query += "JOIN agent a ON c.agent_id = a.agent_id ";
					query += "GROUP BY a.agent_id, a.agent_name;";
					cquery = query.c_str();
					state = mysql_query(connection, cquery);
					if (state != 0) {
						printf("Query Error: %s\n", mysql_error(connection));
					}
					else {
						sql_result = mysql_store_result(connection);
						if (sql_result) {
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("agent_id : %s\nagent_name : %s\nlongest_time_on_market : %s\n", sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
						else {
							printf("No results found.\n");
						}
					}
					printf("\n");
				}
			}
			if (type == 5) {
				printf("---- TYPE V ----\n");
				printf("** Show photos of the most expensive studio, one-bedroom, multi-bedroom apartment(s), and detached house(s), respectively. **\n");
				query = "SELECT property_type, interior_photo, exterior_photo, floor_plan_photo, property_price ";
				query += "FROM ( ";
				query += "SELECT 'Studio' AS property_type, pp.interior_photo, pp.exterior_photo, pp.floor_plan_photo, p.property_price ";
				query += "FROM property_photos pp JOIN property p ON pp.property_id = p.property_id ";
				query += "WHERE p.property_type = 'Studio' ORDER BY p.property_price DESC LIMIT 1 ";
				query += ") AS studio ";
				query += "UNION ALL ";
				query += "SELECT property_type, interior_photo, exterior_photo, floor_plan_photo, property_price ";
				query += "FROM ( ";
				query += "SELECT 'One-bedroom' AS property_type, pp.interior_photo, pp.exterior_photo, pp.floor_plan_photo, p.property_price ";
				query += "FROM property_photos pp JOIN property p ON pp.property_id = p.property_id ";
				query += "WHERE p.property_type = 'Apartment' AND p.property_bedroom = 1 ORDER BY p.property_price DESC LIMIT 1 ";
				query += ") AS one_bedroom ";
				query += "UNION ALL ";
				query += "SELECT property_type, interior_photo, exterior_photo, floor_plan_photo, property_price ";
				query += "FROM ( ";
				query += "SELECT 'Multi-bedroom' AS property_type, pp.interior_photo, pp.exterior_photo, pp.floor_plan_photo, p.property_price ";
				query += "FROM property_photos pp JOIN property p ON pp.property_id = p.property_id ";
				query += "WHERE p.property_type = 'Apartment' AND p.property_bedroom > 1 ORDER BY p.property_price DESC LIMIT 1 ";
				query += ") AS multi_bedroom ";
				query += "UNION ALL ";
				query += "SELECT property_type, interior_photo, exterior_photo, floor_plan_photo, property_price ";
				query += "FROM ( ";
				query += "SELECT 'Detached House' AS property_type, pp.interior_photo, pp.exterior_photo, pp.floor_plan_photo, p.property_price ";
				query += "FROM property_photos pp JOIN property p ON pp.property_id = p.property_id ";
				query += "WHERE p.property_type = 'House' ORDER BY p.property_price DESC LIMIT 1 ";
				query += ") AS detached_house ";
				query += "LIMIT 4;";
				cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Query Error: %s\n", mysql_error(connection));
				}
				else {
					sql_result = mysql_store_result(connection);
					if (sql_result) {
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							printf("property_type : %s\ninterior_photo : %s\nexterior_photo : %s\nfloor_plan_photo : %s\nproperty_price : %s\n",
								sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("No results found.\n");
					}
				}
				printf("\n");
			}
			
			if (type == 6) {
				printf("---- TYPE VI ----\n");
				printf("** Record the sale of a property that had been listed as being available. entails storing the sales price, the buyer, the seller, the agent (if any), and the date. **\n");

				int property_id, buyer_id, seller_id, agent_id;
				double sold_price;
				string sold_date;

				// 사용자 입력 받기
				cout << "Enter property ID: ";
				cin >> property_id;
				cout << "Enter sold price: ";
				cin >> sold_price;
				cout << "Enter buyer ID: ";
				cin >> buyer_id;
				cout << "Enter seller ID: ";
				cin >> seller_id;
				cout << "Enter agent ID (if any, else 0): ";
				cin >> agent_id;
				cout << "Enter sold date (YYYY-MM-DD): ";
				cin >> sold_date;

				// 트랜잭션 시작
				string query = "START TRANSACTION;";
				const char* cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Transaction Start Error: %s\n", mysql_error(connection));
					return 1;
				}

				// 최근 판매된 부동산 테이블에 기록 삽입
				query = "INSERT INTO recently_sold_properties (sold_address, sold_price, sold_type, sold_transaction, sold_bedroom, sold_bathroom, sold_size, school_distance_num, sold_date, sold_resister_date) ";
				query += "SELECT property_address, " + to_string(sold_price) + ", property_type, 'Sale', property_bedroom, property_bathroom, property_size, school_distance_num, '" + sold_date + "', property_resister_date ";
				query += "FROM property WHERE property_id = " + to_string(property_id) + ";";
				cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Insert Error (recently_sold_properties): %s\n", mysql_error(connection));
					mysql_query(connection, "ROLLBACK;");
					return 1;
				}

				// byer_property 테이블에 기록 삽입
				query = "SELECT COUNT(*) FROM byer_property WHERE property_id = " + to_string(property_id) + " AND byer_id = " + to_string(buyer_id) + ";";
				cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Select Error (byer_property): %s\n", mysql_error(connection));
					mysql_query(connection, "ROLLBACK;");
					return 1;
				}
				sql_result = mysql_store_result(connection);
				if (!sql_result) {
					printf("Store Result Error (byer_property): %s\n", mysql_error(connection));
					mysql_query(connection, "ROLLBACK;");
					return 1;
				}
				sql_row = mysql_fetch_row(sql_result);
				int count = atoi(sql_row[0]);
				mysql_free_result(sql_result);

				if (count == 0) {
					query = "INSERT INTO byer_property (property_id, byer_id) VALUES (" + to_string(property_id) + ", " + to_string(buyer_id) + ");";
					cquery = query.c_str();
					state = mysql_query(connection, cquery);
					if (state != 0) {
						printf("Insert Error (byer_property): %s\n", mysql_error(connection));
						mysql_query(connection, "ROLLBACK;");
						return 1;
					}
				}
				else {
					printf("Entry already exists in byer_property, skipping insert.\n");
				}

				// contact 테이블에 기록 삽입 (판매자, 에이전트와 구매자 정보 포함)
				query = "INSERT INTO contact (agent_id, seller_id, byer_id) VALUES (";
				query += to_string(agent_id) + ", " + to_string(seller_id) + ", " + to_string(buyer_id) + ");";
				cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Insert Error (contact): %s\n", mysql_error(connection));
					mysql_query(connection, "ROLLBACK;");
					return 1;
				}

				// 트랜잭션 커밋
				query = "COMMIT;";
				cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Commit Error: %s\n", mysql_error(connection));
					mysql_query(connection, "ROLLBACK;");
					return 1;
				}

				printf("Transaction completed successfully.\n");
			}



			if (type == 7) {
				printf("---- TYPE VII ----\n");
				printf("** Add a new agent to the database **\n");
				string agent_name;
				string agent_phone_number;
				string agent_address;
				cout << "Enter agent name: ";
				cin.ignore();
				getline(cin, agent_name);
				cout << "Enter agent phone number: ";
				getline(cin, agent_phone_number);
				cout << "Enter agent address: ";
				getline(cin, agent_address);

				query = "INSERT INTO agent (agent_name, agent_phone_number, agent_address) ";
				query += "VALUES ('" + agent_name + "', '" + agent_phone_number + "', '" + agent_address + "');";

				const char* cquery = query.c_str();
				state = mysql_query(connection, cquery);
				if (state != 0) {
					printf("Insert Error (agent): %s\n", mysql_error(connection));
				}
				else {
					printf("New agent added successfully.\n");
				}
			}

		}

		// delete and drop table
		ifstream fd;
		fd.open("deletedrop.txt");
		while (getline(fd, line)) {
			const char* qline = line.c_str();
			state = mysql_query(connection, qline);
		}
		fd.close();
		mysql_close(connection);
	}

	return 0;
}