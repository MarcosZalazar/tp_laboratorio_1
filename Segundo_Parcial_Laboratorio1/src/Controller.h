
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_loadFromText(char* path , LinkedList* pListArcades);
int controller_addArcade(LinkedList* pListArcades);
int controller_editArcade(LinkedList* pListArcades,LinkedList* pListaDeJuegos);
int controller_removeArcade(LinkedList* pListArcades);
int controller_ListArcade(LinkedList* pListArcades);
int controller_ListGames(LinkedList* pListaDeJuegos);
int controller_createGameList(LinkedList* pListaDeJuegos, LinkedList* pListaDeArcades);
int controller_saveAsText(char* path , LinkedList* pListArcades);
int controller_saveJuegosAsText(char* path , LinkedList* pListaDeJuegos);
void controller_UpdateListGames(LinkedList* pListaDeJuegos);
int controller_createMultijugadorList(LinkedList* listaMultijugadores);
int controller_updateNumberOfCoins(LinkedList* pListaDeArcades);
int controller_exitDelete(LinkedList* pListArcades);

#endif /* CONTROLLER_H_ */
