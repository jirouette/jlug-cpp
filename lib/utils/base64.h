#ifdef __cplusplus
extern "C"
{
#endif

/*
   Fichier base64.h
   Auteur Bernard Chardonneau
*/

/* prototypes des fonctions de la bibliothèque base64 */

void encode64 (char *orig, char *dest, int nbcar);
int  decode64 (unsigned char *buffer);

#ifdef __cplusplus
}
#endif
