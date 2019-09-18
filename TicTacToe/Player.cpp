#include "stdafx.h"
#include "Player.h"

Player::Player() {

}

Player::~Player() {}

/*======================================================================================================
  =================================Estadisticas del jugador=============================================
  ====================================================================================================== */

  /*La ubicacion del jugador cambiará con esta funcion
	  @param numero del cuarto al que se va a pasar
	  @return nueva pocision del jugador*/
void Player::setCurrentRoom(int room) {
	previousRoom = currentRoom;
	this->currentRoom = room;

}

/*Regresarle al jugador su ubicacion actual en la dungeon*/
int Player::getCurrentRoom() {
	return currentRoom;
}

/*Regresarle al jugador su ubicacion anterior en la dungeon*/
int Player::getPreviousRoom() {
	return previousRoom;
}

/*Obtener el daño actual del jugador*/
int Player::getDamage() {
	return damage;
}

/*Actualizar el daño actual del jugador*/
void Player::setDamage(int d) {
	damage = d;
}

/*Actualizar la defensa del jugador*/
void Player::setDefense(int d) {
	defense = d;
}

/*Regresarle la defensa actual al jugador*/
int Player::getDefense() {
	return defense;
}

/*Regresarle la vida actual al jugador*/
int Player::getCurrentHealth() {
	return currentHealth;
}

/*Regresarle la vida máxima al jugador*/
int Player::getMaximumHealth()
{
	return maximumHealth;
}

/*actualizar la vida máxima*/
void Player::setMaximumHealth(int maxH)
{
	maximumHealth = maxH;
}

/*Actualizar la vida actual*/
void Player::setCurrentHealth(int h) {
	currentHealth = h;
}


/*======================================================================================================
  =================================Acciones del jugador=================================================
  ====================================================================================================== */


  /*El jugador puede abrir la puerta que quiera, esto le permitirá pasar al siguiente cuarto siempre y cuando la puerta esté desbloqueada. En
	caso de que no sea así, le dirá que está bloqueada y que necesita una llave.
	  @param contenedor de cuartos, posición del jugador en el contenedor, número de puerta que se quiere abrir.*/
void Player::openDoor(map<int, Room> roomMap, int playerPos, int doorNumber, HWND hWnd) {

	//Se recorre el contenedor de puertas, si solo si hay puertas
	for (Door& door : roomMap.at(playerPos).doorList) {
		if (roomMap.at(playerPos).doorList.max_size() > 0) {
			if (doorNumber == door.getID()) {

				if (door.getStatus() == false) {
					MessageBoxA(hWnd, "Puerta cerrada.", "Investigando puertas", MB_OK);
					
				}
				else if (door.getStatus() == true) {
					
					string status = "Puerta abierta, ahora te encuentras en el cuarto: " + to_string(door.getID());
					stringToMessageBox(status, hWnd);
					setCurrentRoom(door.getID());
				}

			}

		}
	}



}

/*El jugador decidirá qué puerta desbloquear, si está bloqueada buscará en el llavero del jugador una llave que tenga el mismo ID de la puerta
en caso de que no haya ninguna llave con el ID, marcará error y se lo dirá al jugador.
		@param contenedor de cuartos, posición del jugador en el contenedor, numero que el jugador ingresa.
		@return puerta desbloqueada o notificacion de que no se tiene una llave que la abra.*/
void Player::unlockDoor(map<int, Room>& roomMap, int playerPos, int doorNumber, HWND hWnd) {
	
	
	string doorNumberr;
	for (forward_list<Door> ::iterator _doorIterator = roomMap.at(playerPos).doorList.begin(); _doorIterator != roomMap.at(playerPos).doorList.end(); _doorIterator++) {

		if (doorNumber == _doorIterator->getID() || _doorIterator->getStatus() == false) {

			doorNumberr = "Puerta numero: " + to_string(_doorIterator->getID());
			stringToMessageBox(doorNumberr, hWnd);

			if (newKeyVector.size() > 0) {
				for (vector <Key> ::iterator _iterator = newKeyVector.begin(); _iterator != newKeyVector.end(); _iterator++) {
					if (_iterator->getAtribute() == _doorIterator->getID()) {
						_doorIterator->setStatus(true);
						stringToMessageBox("Puerta abierta, puedes pasar en cualquier momento por ahi.", hWnd);
						try {
							//keyVector.erase(remove(keyVector.begin(), keyVector.end(), _iterator));
						}
						catch (std::exception& e) {
							stringToMessageBox(e.what(), hWnd);
						}

						break;

					}
					else
						stringToMessageBox("Ninguna llave en tu poder puede abrir alguna de estas puertas.\n\n", hWnd);
				}
			}
			else stringToMessageBox("No tienes ninguna llave.", hWnd);
		}
	
	}


}


/* Para que el jugador se pueda curar, se recorre el arreglo de vectores de pociones. Si hay al menos una, se le muestran al jugador su nombre y los puntos que cura. Al momento
que elige el jugador que pocion usar, se revisa la vida actual del jugador, si es menor a la vida maxima, se cura lo que de la poción. Si la poción lo cura más allá de la
vida máxima, la vida actual no sobrepasa ese limite. Si la vida actual ya es igual a la vida máxima, no se puede curar */
void Player::heal(HWND hWnd, HWND textBox) {
	string items;
	
	if (potionVector.size() > 0) {
		stringToMessageBox("Tienes las siguientes pociones en tu inventario.", hWnd);
		vector<HealthPotion> ::iterator _iterator = potionVector.begin();
		std::advance(_iterator, 1);
		items = _iterator->getName() + " puntos que cura: " + to_string(_iterator->getAtribute());
		stringToMessageBox(items, hWnd);
		_iterator++;

		/*for (vector<HealthPotion> ::iterator _iterator = potionVector.begin(); _iterator != potionVector.end(); _iterator++) {
			items = _iterator->getName() + " puntos que cura: " + to_string(_iterator->getAtribute());
			stringToMessageBox(items, hWnd);

		}*/

		stringToMessageBox("Elige la pocion con la que quieras curarte.", hWnd);
		char textReaded[20];
		int length = GetWindowTextLength(textBox) + 1;
		GetWindowTextA(textBox, textReaded, length);

		for (HealthPotion healthP : potionVector) {

			if (textReaded == healthP.getName()) {
				obteniendoDatos(getCurrentHealth(), healthP.getAtribute());
				if (sumandoDatos() < getMaximumHealth()) {
					stringToMessageBox("Curacion realizada.", hWnd);
					setCurrentHealth(sumandoDatos());

					potionVector.erase(remove(potionVector.begin(), potionVector.end(), healthP));
					potionVector.shrink_to_fit();

				}

				else if (currentHealth == getMaximumHealth()) {
					stringToMessageBox("No puedes curarte ms de esto.", hWnd);
				}

				else if (sumandoDatos() > getMaximumHealth()) {
					currentHealth = getMaximumHealth();
					setCurrentHealth(currentHealth);
					potionVector.erase(remove(potionVector.begin(), potionVector.end(), healthP));
					potionVector.shrink_to_fit();
				}

			}
			else
				printf("esa pocion no esta en el inventario de pociones.");

		}

	}
	else
		printf("No hay pociones en tu inventario con las cuales curarte.\n");
}

/*A partir de todo lo que haga el jugador, curarse, tomar armas y escudo, etc. Se desplegara toda la información.*/
string Player::openStats(HWND hWnd) {
	stringToMessageBox("Estas son tus siguientes estadisticas:", hWnd);
	string stats = "Vida Actual: " + to_string(getCurrentHealth()) + "/" + to_string(getMaximumHealth()) +  "\nDano actual: " + to_string(getDamage()) + "\nDefensa actual: " + to_string(getDefense())
		+ "\nCuarto Actual: " + to_string(getCurrentRoom());
	stringToMessageBox(stats, hWnd);
	return stats;
}


/*	Se recorrerán los elementos de cada contenedor y mostrará su información en caso de que el tamaño de dichos contenedores sea mayor a cero.
	@param el contenedor de los cuartos, pocisión del jugador.
	@return los elementos de cada contenedor dentro de los cuartos. */
void Player::revealCurrentRoom(map<int, Room>& roomMap, int playerPos, HWND hWnd) {

	stringToMessageBox("Puertas disponibles:", hWnd);
	string datos;
	for (Door &a : roomMap.at(playerPos).doorList) {
		if (a.getStatus() == false) {
			datos = "Puerta Numero: " + to_string((int&)a) + " Cerrado";

			stringToMessageBox(datos, hWnd);

		}
		else {
			datos = "Puerta Numero: " + to_string((int&)a) + " Abierto";
			stringToMessageBox(datos, hWnd);
		}
	
	}

	if (roomMap.at(playerPos).enemyVector.size() > 0) {
		stringToMessageBox("Enemigos en la habitacion", hWnd);
		for (Enemy *a : roomMap.at(playerPos).enemyVector) {
			datos = "Nombre del Enemigo: " + a->getEnemyName() + "Vida del enemigo: " +  to_string(a->getEnemyHealth()) + "\nFuerza del enemigo: " 
				+ to_string(a->getEnemyStrength()) + "\nDefensa del enemigo: " + to_string(a->getEnemyDefense());
			stringToMessageBox(datos, hWnd);

		}
	}
	else stringToMessageBox("No hay enemigos en esta habitacion.", hWnd);



	if (roomMap.at(playerPos).itemsVector.size() > 0) {
		stringToMessageBox("Objetos disponibles.", hWnd);
		
		for (Items* a : roomMap.at(playerPos).itemsVector) {
			datos = "Nombre del objeto: " + a->getName() + "\nValor del objeto: " + to_string(a->getAtribute());
			stringToMessageBox(datos, hWnd);

		}
	}
	else stringToMessageBox("No hay objetos en esta habitacion.", hWnd);
	
}

/*======================================================================================================================
  =====================================================Crafteo==========================================================
  ======================================================================================================================*/

string Player::crafting(HWND hWnd, HWND textBox)
{
	stringToMessageBox("Elige el nombre del arma que quieras craftear", hWnd);
	recipeBook(hWnd);
	char textReaded[20];
	int length = GetWindowTextLength(textBox) + 1;
	GetWindowTextA(TextBox, textReaded, length);

	diccionario(textReaded, textBox, hWnd);
	return textReaded;
}

void Player::recipeBook(HWND hWnd)
{
	std::forward_list<string> recetario = {
		"diente de dragon: Espada de madera + Espada de diamante.",
		"espada de aluminio: Espada de metal + espada de hule.",
		"escudo de papel: Escudo de diamantina + escudo de madera."
	};
	for (std::forward_list<string>::iterator it = recetario.begin(); it != recetario.end(); it++) {
		stringToMessageBox(*it, hWnd);
	}


}

void Player::diccionario(string sentence, HWND textBox, HWND hWnd)
{

	map<int, vector<string>> diccionario{
		{0,{"diente de dragon"}},
		{1,{"espada de aluminio"}},
		{2,{"escudo de papel"}}
	};

	char textReaded[20];
	int length = GetWindowTextLength(textBox) + 1;
	GetWindowTextA(textBox, textReaded, length);

	particionDeString(diccionario, sentence, hWnd);

}

void Player::particionDeString(map<int, vector<string>> search, string sentence, HWND hWnd) {
	std::for_each(sentence.begin(), sentence.end(), [](char& c) {
		c = ::tolower(c);
	});

	int numero = 0;
	for (map< int, vector<string>> ::iterator _firstMapIterator = search.begin(); _firstMapIterator != search.end(); _firstMapIterator++) {
		for (vector<string> ::iterator it = _firstMapIterator->second.begin(); it != _firstMapIterator->second.end(); it++) {
			if (sentence == *it) {
				stringToMessageBox(sentence, hWnd);
				numero = (int)_firstMapIterator->first;
				switchForWeapons(numero, hWnd);
			}
		}
	}


}

void Player::switchForWeapons(int number, HWND hWnd)
{
	switch (number)
	{
	case 0:
		dragonsTeeth(hWnd);
		break;
	}
}

/*======================================================================================================================
  =====================================================Creacion de armas================================================
  ======================================================================================================================*/

Sword * Player::dragonsTeeth(HWND hWnd)
{
	bool firstSword = false;
	bool secondSword = false;
	for (Items sword : itemsVector) {
		Items* thisSword = &sword;
		if (thisSword == static_cast<Sword*>(thisSword)) {
			if (thisSword->getName() == "Espada de diamante") {
				stringToMessageBox("Segunda espada conseguida.", hWnd);
				firstSword = true;
			}
			else if (thisSword->getName() == "Espada de madera") {
				stringToMessageBox("Primer espada conseguida.", hWnd);
				secondSword = true;
			}
		}
	}
	if (secondSword == true || firstSword == true) {
		Sword* dragonTeeth = new Sword("Diente de dragon", 20);
		itemsVector.clear();
		Items items = *dragonTeeth;
		itemsVector.push_back(items);
		return dragonTeeth;
	}
	else
		return 0;
}


/*=================================================================================================================
  =====================================Recoger armas===============================================================
  =================================================================================================================*/

  /*El jugador podrá recoger la espada que se encuentre en el cuarto actual.
	  @param contenedor donde se encuentren los cuartos del juego, posición del jugador
	  @return recupera la espada del cuarto y la elimina del contenedor de la recámara.*/
void Player::pickUpSword(map<int, Room> &roomMap, int playerPos) {

	//Itera el contenedor de items en el cuarto
	for (Items* items : roomMap.at(playerPos).itemsVector) {

		try {
			//si el item es de tipo espada, realiza las siguientes acciones.
			if (items == dynamic_cast<Sword*>(items)) {
				printf("Tu ataque ahora contiene el poder de esta espada.\n\n");
				setDamage(items->getAtribute()); //al momento de agarrar la espada, el daño se le pasa al jugador como estadística
				itemsVector.push_back(*items); //se agrega al inventario del jugador.
				roomMap.at(playerPos).itemsVector.erase(remove(roomMap.at(playerPos).itemsVector.begin(), roomMap.at(playerPos).itemsVector.end(), items)); //se elimina del cuarto
				roomMap.at(playerPos).itemsVector.shrink_to_fit();
				break;
			}
			else
				printf("No hay espadas en este cuarto\n\n");
		}
		catch (std::bad_alloc& e) { //si falla en añadirse, suelta esta excepción.
			cout << "bad alloc: " << e.what() << "\n\n";
		}
	}

}


/*El jugador podrá recoger el escudo que se encuentre en el cuarto actual.
	@param contenedor donde se encuentren los cuartos del juego, posición del jugador
	@return recupera el escudo del cuarto y lo elimina del contenedor de la recámara.*/
void Player::pickUpShield(map<int, Room> &roomMap, int playerPos) {
	//Itera el contenedor de items en el cuarto
	for (Items* items : roomMap.at(playerPos).itemsVector) {

		try {
			//si el item es de tipo espada, realiza las siguientes acciones.
			if (items == dynamic_cast<Shield*>(items))
			{
				printf("Tu defensa ahora es similar al poder de este escudo.\n\n");
				setDefense(items->getAtribute()); //la defensa del escudo pasa a ser parte del jugador
				obteniendoDatos(items->getAtribute(), getMaximumHealth());
				setMaximumHealth(sumandoDatos());
				//sumandoDatos();
				itemsVector.push_back(*items);//se agrega al inventario del jugador.
				roomMap.at(playerPos).itemsVector.erase(remove(roomMap.at(playerPos).itemsVector.begin(), roomMap.at(playerPos).itemsVector.end(), items));//se elimina del cuarto
				roomMap.at(playerPos).itemsVector.shrink_to_fit();
				break;

			}
		}
		catch (std::bad_alloc& e) {
			cout << "bad alloc: " << e.what() << "\n\n";
		}
	}
}



/*El jugador podrá recoger la llave que se encuentre en el cuarto actual.
	@param contenedor donde se encuentren los cuartos del juego, posición del jugador
	@return recupera la llave del cuarto y la elimina del contenedor de la recámara.*/
void Player::pickUpKey(map<int, Room> &roomMap, int playerPos) {

	//itera el contenedor de objetos
	if (newKeyVector.size() < 2) {
		for (Items* items : roomMap.at(playerPos).itemsVector) {
			try {
				//si el tipo de objeto es de tipo Llave, realiza lo siguiente
				if (items == dynamic_cast<Key*>(items)) {
					cout << "Llave " << items->getName() << " conseguido!\n\n";

					Key* myKey = dynamic_cast<Key*>(items); //convierte el item en llave para poder introducirlo al contenedor
					newKeyVector.push_back(*myKey); //se agrega al llavero del jugador

					roomMap.at(playerPos).itemsVector.erase(remove(roomMap.at(playerPos).itemsVector.begin(), roomMap.at(playerPos).itemsVector.end(), items)); //se elimina del cuarto
					roomMap.at(playerPos).itemsVector.shrink_to_fit();
					break;

				}
			}
			catch (std::bad_alloc& e) {
				cout << "bad alloc: " << e.what() << "\n\n";
			}
		}
	}
	else if (newKeyVector.size() >= 2) {
		dropKey(roomMap, playerPos);
	}
}



/*El jugador podrá recoger la poción que se encuentre en el cuarto actual.
	@param contenedor donde se encuentren los cuartos del juego, posición del jugador
	@return recupera la poción del cuarto y la elimina del contenedor de la recámara.*/
void Player::pickUpPotion(map<int, Room> &roomMap, int playerPos) {
	//se itera el contenedor de objetos
	for (Items* items : roomMap.at(playerPos).itemsVector) {

		try {
			//si el objeto es de tipo poción curativa, se realiza lo siguiente
			if (items == dynamic_cast<HealthPotion*>(items)) {
				cout << "Llave " << items->getName() << " conseguido!\n\n";
				HealthPotion* myPotion = dynamic_cast<HealthPotion*>(items); //se castea el objeto para poder entrar al contenedor
				potionVector.push_back(*myPotion); //se agrega al contenedor del jugador
				roomMap.at(playerPos).itemsVector.erase(remove(roomMap.at(playerPos).itemsVector.begin(), roomMap.at(playerPos).itemsVector.end(), items)); // se elimina del cuarto
				break;

			}
		}
		catch (std::bad_alloc& e) {
			cout << "bad alloc: " << e.what() << "\n\n";
		}
	}
}



/*=================================================================================================================
  =====================================Tirar armas===============================================================
  =================================================================================================================*/


  /*El jugador podra tirar la espada que quiera tirar y dejarla en el cuarto actual.*/
void Player::dropSword(map<int, Room>& roomMap, int playerPos) {

	if (itemsVector.size() > 0)
	{
		openInventory();
		string nombre;
		printf("Elige el nombre de la espada que quieras tirar.\n\n");
		std::cin.clear();
		std::getline(std::cin, nombre);

		for (Items& sword : itemsVector)
		{
			Items* dropThisSword = &sword;
			if (dropThisSword == static_cast<Sword*>(dropThisSword))
			{
				if (nombre == sword.getName()) {
					Sword* thisSword = dynamic_cast<Sword*>(dropThisSword);
					roomMap.at(playerPos).itemsVector.push_back(thisSword);
					itemsVector.erase(remove(itemsVector.begin(), itemsVector.end(), sword));
					itemsVector.shrink_to_fit();
					setDamage(0);
					printf("Espada removida con exito\n");
				}
			}
			else printf("\nNo hay espadas en tu inventario.\n\n");
		}
	}
	else printf("\nNo tienes objetos (espadas ni escudos) en tu inventario.\nn");

}

/*El jugador podra tirar el escudo que quiera tirar y dejarla en el cuarto actual.*/
void Player::dropShield(map<int, Room>& roomMap, int playerPos) {
	if (itemsVector.size() > 0)
	{
		openInventory();
		string nombre;
		printf("Elige el nombre de la escudo que quieras tirar.\n\n");
		std::cin.clear();
		std::getline(std::cin, nombre);

		for (Items shield : itemsVector)
		{
			if (nombre == shield.getName()) {
				Items* dropThisShield = &shield;
				if (dropThisShield == static_cast<Shield*>(dropThisShield)) {
					roomMap.at(playerPos).itemsVector.push_back(dropThisShield);
					itemsVector.erase(remove(itemsVector.begin(), itemsVector.end(), shield));
					itemsVector.shrink_to_fit();
					setDefense(0);
					printf("Escudo removido con exito.\n");
				}
				else printf("\nNo hay escudos en tu inventario.\n\n");

			}
			else
				printf("Nombre incorrecto.\n");
		}
	}
	else printf("\nNo tienes objetos (espadas ni escudos) en tu inventario.\nn");
}

/*El jugador podra tirar la llave que quiera tirar y dejarla en el cuarto actual.*/
void Player::dropKey(map<int, Room>& roomMap, int playerPos)
{
	if (newKeyVector.size() > 0) {
		openInventory();
		int id;
		string nombre;
		printf("\nElige el id de la llave que quieras tirar.\n\n");
		std::cin >> id;
		for (Key& key : newKeyVector)
		{
			if (id == (int)key.getDoorID()) {

				cout << "la llave: " << key.getName() << " sera eliminada de tu inventario.\n";

				Key* dropThisKey = &key;

				newKeyVector.erase(remove(newKeyVector.begin(), newKeyVector.end(), key));
				newKeyVector.shrink_to_fit();
				try {
					//roomMap.at(playerPos).itemsVector.resize(roomMap.at(playerPos).itemsVector.size() + 1);
					roomMap.at(playerPos).itemsVector.push_back(dropThisKey);
				}
				catch (std::exception& e) {
					cout << "Exception caught: " << e.what() << "\n";
				}

				break;

			}
			else printf("\nElige el nombre de una llave que si este en el llavero.\n\n");

		}
		std::cin.ignore();
	}

	else printf("\nNo tienes ninguna llave en tu llavero.\n\n");
}

/*El jugador podra tirar la pocion que quiera tirar y dejarla en el cuarto actual.*/
void Player::dropPotion(map<int, Room>& roomMap, int playerPos)
{
	if (potionVector.size() > 0) {

		openInventory();
		string nombre;
		printf("Elige el nombre de la pocion que quieras tirar.\n\n");
		std::getline(std::cin, nombre);;

		for (HealthPotion& potion : potionVector)
		{
			if (nombre == potion.getName())
			{
				cout << "La pocion: " << potion.getName() << " sera eliminada de tu inventario.\n";

				HealthPotion* dropThisPotion = &potion;
				potionVector.erase(remove(potionVector.begin(), potionVector.end(), potion));
				potionVector.shrink_to_fit();

				roomMap.at(playerPos).itemsVector.push_back(dropThisPotion);


				break;
			}
			else printf("\nElige el nombre de una pocion que este en tu inventario.\n\n");
		}
	}
	else printf("\nNo tienes pociones en tu inventario.\n\n");
}

/* El jugador tendrá la oportunidad de checar su inventario en cualquier momento del juego*/
void Player::openInventory() {
	if (itemsVector.size() > 0) {

		printf("\nEstos son los objetos en tu inventario de armas:\n");
		for (Items& item : itemsVector) {

			cout << item.getName() << "\n";

		}
	}
	else
		printf("\nTu inventario de armas esta vacio.\n");

	//===========================================================================================
	if (newKeyVector.size() > 0) {

		printf("\nEstas son las llaves en tu llavero:\n");
		for (Key key : newKeyVector) {

			cout << key.getName() << " con el Id: " << key.getAtribute() << "\n";
		}

	}
	else
		printf("\nTu llavero esta vacio.\n");


	//===========================================================================================

	if (potionVector.size() >= 1) {

		printf("\nEstas son las pociones en tu inventario.\n");
		for (HealthPotion& potion : potionVector) {

			cout << potion.getName() << "\n";

		}printf("\n");
	}
	else
		printf("\nTu contenedor de pociones esta vacio.\n");
}

/*	===========================================================================================================================================
	===========================================================PELEA CON ENEMIGOS==============================================================
	=========================================================================================================================================== */


	/*Si en el contenedor de cuartos hay un contenedor de enemigos con el tamaño de minions mayor a cero, la pelea empieza.
	Se recorre el arreglo de los enemigos y luego busca si cada uno tiene mayo vida a 0. Después entra en un while en el que se revisa el daño del jugador y el daño del enemigo, se hace una resta y se quitan puntos de vida.
	Posteriormente entra en un while de defensa, en el cual el enemigo ataca al jugador. El ciclo se repite hasta que el enemigo de cada indice sea igual o menor a cero. Al morir, va al siguiente enemigo.
	Si el jugador muere regresa al cuarto anterior.*/
void Player::fightingMinions(map<int, Room>& roomMap, int playerPos, HWND hWnd) {
	bool fighting, defense;
	if (roomMap.at(playerPos).enemyVector.size() > 0) {
		MessageBoxA(hWnd, "El/Los enemigo/s dentro de esta habitacion es/son peligrosos, ten cuidado a pesar de que pueden ser faciles de matar, puede ser dificil de pelear con ellos.", "Peleando", MB_OK);
		for (Enemy* minion : roomMap.at(playerPos).enemyVector)

			if (minion = dynamic_cast<Minion*>(minion)) {

		

				if (minion->getEnemyHealth() > 0) {
					fighting = true;
					char buff[200] = "";
					string name = "Preparate para luchar! Empiezas tu atacando. El enemigo: " + minion->getEnemyName() + " se defiende de tu ataque con " 
									   + std::to_string(minion->getEnemyDefense()) + " puntos de defensa. Por lo tanto, recibe: " + std::to_string(damageInFight(getDamage(), minion->getEnemyDefense()))
									   + " puntos de dano.\n";
					while (fighting) {

						stringToMessageBox(name, hWnd);

						if (damageInFight(getDamage(), minion->getEnemyDefense()) == 0) minion->setMinionHealth(minion->getEnemyHealth());
						else minion->setMinionHealth(damageInFight(minion->getEnemyDefense(), getDamage()));

						name = "Vida restante del enemigo: " + std::to_string(minion->getEnemyHealth());
						stringToMessageBox(name, hWnd);
						defense = true;

						if (minion->getEnemyHealth() <= 0) {
							fighting = false;
							MessageBoxA(hWnd, "Enemigo asesinado!\n\n", "Sin enemigos", MB_OK); defense = false;
						} 



						while (defense) {
							MessageBoxA(hWnd, "Preparate para defenderte.! El enemigo empieza atacando.", "Defiendete", MB_OK);
							name = "El enemigo: " +  minion->getEnemyName() + " ataca con: " +  std::to_string(minion->getEnemyStrength()) +  " puntos de ataque. Por lo tanto, recibes: "
								+  to_string(damageInFight(getDefense(), minion->getEnemyStrength())) + " puntos de dano.\n";
							stringToMessageBox(name, hWnd);


							if (damageInFight(getDefense(), minion->getEnemyStrength()) == 0) setCurrentHealth(getCurrentHealth());
							else setCurrentHealth(damageInFight(getDefense(), minion->getEnemyStrength()));
							name = "Tu vida restante: " + to_string(getCurrentHealth());

							if (getCurrentHealth() <= 0) {
								MessageBoxA(hWnd, "Has muerto, sera momento de encontrar mejor armadura.", "Sin enemigos", MB_OK); defense = false;
								setCurrentRoom(getPreviousRoom());
								fighting = false;
							} defense = false;
						}

					}
				}
				else
					MessageBoxA(hWnd, "No hay ningun enemigo vivo", "Sin enemigos", MB_OK); defense = false;

			}

	}
	else MessageBoxA(hWnd, "No hay enemigos en esta habitacion.\n", "", MB_OK);
}

/*
Si en el contenedor de cuartos hay un contenedor de enemigos con el tamaño de jefes mayor a cero, la pelea empieza.
Se recorre el arreglo de los enemigos y luego busca si cada uno tiene mayo vida a 0. Después entra en un while en el que se revisa el daño del jugador y el daño del enemigo, se hace una resta y se quitan puntos de vida.
Posteriormente entra en un while de defensa, en el cual el enemigo ataca al jugador. El ciclo se repite hasta que el enemigo de cada indice sea igual o menor a cero. Al morir, va al siguiente enemigo.
Si el jugador muere regresa al cuarto anterior.
*/
void Player::fightingBosses(map<int, Room>& roomMap, int playerPos) {
	bool fighting, defense;

	if (roomMap.at(playerPos).enemyVector.size() > 0)
	{

		for (Enemy* boss : roomMap.at(playerPos).enemyVector)
		{
			if (boss = dynamic_cast<Boss*>(boss)) {
				printf("Vas a enfrentarte contra uno o varios jefes, ten cuidado, pueden ser complicado darles pelea, puedes morir fácilmente.\n\n");

				if (boss->getEnemyHealth() > 0)
				{
					fighting = true;
					while (fighting)
					{

						cout << "Preparate para luchar! Empiezas tu atacando.\n"
							<< "El enemigo: " << boss->getEnemyName() << " se defiende de tu ataque con " << boss->getEnemyDefense() << " puntos de defensa. Por lo tanto, recibe: "
							<< damageInFight(boss->getEnemyDefense(), getDamage()) << " puntos de dano.\n";

						if (damageInFight(boss->getEnemyDefense(), getDamage()) == 0)
							boss->setMinionHealth(boss->getEnemyHealth());

						else
							boss->setMinionHealth(damageInFight(boss->getEnemyDefense(), getDamage()));

						cout << "Vida restante del enemigo: " << boss->getEnemyHealth() << "\n\n";

						if (boss->getEnemyHealth() <= 0)
						{
							fighting = false;

							roomMap.at(playerPos).enemyVector.erase(remove(roomMap.at(playerPos).enemyVector.begin(), roomMap.at(playerPos).enemyVector.end(), boss));
							roomMap.at(playerPos).enemyVector.shrink_to_fit();
							printf("Enemigo asesinado!\n");

						} defense = true;

						printf("Preparate para defenderte.! El enemigo empieza atacando.\n");

						while (defense)
						{
							cout << "El enemigo: " << boss->getEnemyName() << " ataca con: " << boss->getEnemyStrength() << " puntos de ataque. Por lo tanto, recibes: "
								<< damageInFight(getDefense(), boss->getEnemyStrength()) << " puntos de dano.\n";

							if (damageInFight(getDefense(), boss->getEnemyStrength()) == 0) setCurrentHealth(getCurrentHealth());
							setCurrentHealth(damageInFight(getDefense(), boss->getEnemyStrength()));
							cout << "Tu vida restante: " << getCurrentHealth() << "\n\n";

							if (getCurrentHealth() <= 0)
							{
								printf("Has muerto, sera momento de encontrar mejor armadura.\n");
								setCurrentRoom(getPreviousRoom());
							} defense = false;
						}
					}
				}
				else printf("Este jefe esta muerto\n");
			}
			else printf("No hay jefes en esta habitacion.\n");
		}
	}

}

void Player::fightingFinalBoss(map<int, Room>& roomMap, int playerPos)
{
	bool fighting, defense;

	if (roomMap.at(playerPos).enemyVector.size() > 0)
	{

		for (Enemy* finalBoss : roomMap.at(playerPos).enemyVector)
		{
			if (finalBoss = dynamic_cast<FinalBoss*>(finalBoss)) {
				printf("Vas a enfrentarte contra uno o varios jefes, ten cuidado, pueden ser complicado darles pelea, puedes morir fácilmente.\n\n");

				if (finalBoss->getEnemyHealth() > 0)
				{
					fighting = true;
					while (fighting)
					{
						cout << "Preparate para luchar! Empiezas tu atacando.\n"
							<< "El enemigo: " << finalBoss->getEnemyName() << " se defiende de tu ataque con " << finalBoss->getEnemyDefense() << " puntos de defensa. Por lo tanto, recibe: "
							<< damageInFight(finalBoss->getEnemyDefense(), getDamage()) << " puntos de dano.\n";

						if (damageInFight(finalBoss->getEnemyDefense(), getDamage()) == 0)
							finalBoss->setMinionHealth(finalBoss->getEnemyHealth());

						else
							finalBoss->setMinionHealth(damageInFight(finalBoss->getEnemyDefense(), getDamage()));

						cout << "Vida restante del enemigo: " << finalBoss->getEnemyHealth() << "\n\n";

						if (finalBoss->getEnemyHealth() <= 0)
						{
							fighting = false;
							gameIsActive = false;
							roomMap.at(playerPos).enemyVector.erase(remove(roomMap.at(playerPos).enemyVector.begin(), roomMap.at(playerPos).enemyVector.end(), finalBoss));
							roomMap.at(playerPos).enemyVector.shrink_to_fit();
							printf("Enemigo asesinado! \n\nY asi es como termina la historia, tu, nuestro heroe lograste cumplir el objetivo que muchas personas creian imposible."
								"\nLograste ser un rey cuando no lo habias pedido y sin embargo, fuiste el mejor que ese reino pudo haber tenido.");

						} defense = true;

						printf("Preparate para defenderte.! El enemigo empieza atacando.\n");

						while (defense)
						{
							cout << "El enemigo: " << finalBoss->getEnemyName() << " ataca con: " << finalBoss->getEnemyStrength() << " puntos de ataque. Por lo tanto, recibes: "
								<< damageInFight(getDefense(), finalBoss->getEnemyStrength()) << " puntos de dano.\n";

							if (damageInFight(getDefense(), finalBoss->getEnemyStrength()) == 0) setCurrentHealth(getCurrentHealth());
							setCurrentHealth(damageInFight(getDefense(), finalBoss->getEnemyStrength()));
							cout << "Tu vida restante: " << getCurrentHealth() << "\n\n";

							if (getCurrentHealth() <= 0)
							{
								printf("Has muerto, sera momento de encontrar mejor armadura.\n");
								setCurrentRoom(getPreviousRoom());
							} defense = false;
						}
					}
				}
				else printf("Este jefe esta muerto\n");
			}
			else printf("No hay jefes en esta habitacion.\n");
		}
	}
}

