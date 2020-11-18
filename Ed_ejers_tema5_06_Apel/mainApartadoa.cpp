// Examen junio 2016
// Implementación de un sistema de reproducción de música

#include <iostream>
#include <string>
#include "lista.h"
#include "DiccionarioHash.h"

using namespace std;


typedef string Cancion;
typedef string Artista;


// Aquí definimos clase equivalente a lo dado en el enunciado
class SongInfo {
public:
	Artista artist;
	int duration;
	Lista<Cancion>::Iterator it_playlist;
	Lista<Cancion>::Iterator it_played;
	bool inPlaylist;
	bool played;

	//SongInfo(): inPlaylist(false), played (false) {}
	SongInfo(
		const Lista<Cancion>::Iterator& it_playlist,
		const Lista<Cancion>::Iterator& it_played
	):
		it_playlist(it_playlist), it_played(it_played), inPlaylist(false), played(false) {}
};

// clases excepcion para iPud
class ECancionExistente{};
class ECancionNoExistente{};

// clase iPud
class iPud {
	DiccionarioHash<Cancion,SongInfo> _dic_songs;
	Lista<Cancion> _playlist;
	Lista<Cancion> _played;
	int _duration;
	int _duration_playlist;
    
public:
	iPud() : _duration(0), _duration_playlist(0) {}
	void addSong(const Cancion& c, const Artista& a, int d);
	void addToPlaylist(const Cancion& c);
	void deleteSong(const Cancion& c);
	void play();
	Cancion current();
	int totalTime();
	Lista<Cancion> recent(int n);
};

//addSong(S, A, D) : Añade la canción S(string) del artista A(string) 
//con duración D(int) al iPud.Si ya existe una canción con el mismo 
//nombre la operación dará error.

// Añade una cancion al ipud.
void iPud::addSong(const Cancion& c, const Artista& a, int d) {
	// CONSTANTE
	if (_dic_songs.contiene(c))
		throw ECancionExistente();

	SongInfo nueva_cancion(_playlist.end(), _played.end());
	nueva_cancion.artist = c;
	nueva_cancion.duration = d;
	nueva_cancion.inPlaylist = false;
	nueva_cancion.played = false;
	_dic_songs.inserta(c, nueva_cancion);
	_duration += d;
}
	
//addToPlaylist(S) : Añade la canción S al final de la lista de 
//reproducción.Si la canción ya se encontraba en la lista entonces 
//no se añade(es decir, la lista no tiene canciones repetidas).
//Si la canción no está en el iPud se devuelve error.

// Añade una cancion a la lista de reproduccion
void iPud::addToPlaylist(const Cancion& c)
{
	// CONSTANTE
	if (!_dic_songs.contiene(c))
		throw ECancionNoExistente();

	DiccionarioHash<Cancion, SongInfo>::Iterator it = _dic_songs.busca(c);
	if (!it.valor().inPlaylist) 
	{
		_playlist.pon_ppio(c);
		it.valor().it_playlist = _playlist.begin();
		it.valor().inPlaylist = true;
		_duration_playlist += it.valor().duration;
	}
}

//current: Devuelve la primera canción de la lista de reproducción.
//Si es vacía se devuelve error.

// devuelve la primera cancion de la lista de reproduccion
Cancion iPud::current(){
	// CONSTANTE
	if (_playlist.esVacia())
		throw EListaVacia();

	return _playlist.ultimo();
}

//totalTime:  Obtiene  la  suma  de  las  duraciones  de  las  canciones 
//que integran la lista de reproducción actual.
//Si es vacía se devuelve 0.

// Devuelve el tiempo total de la lista de reproduccion
int iPud::totalTime(){
	// CONSTANTE
	if (_playlist.esVacia())
		return 0;

	return _duration_playlist;
}

//deleteSong(S) : Elimina todo rastro de la canción S.
//Si la canción no existe la operación no tiene efecto.

// Elimina una cancion del ipud
void iPud::deleteSong(const Cancion& c){
	// CONSTANTE
	if (_dic_songs.contiene(c)) {
		DiccionarioHash<Cancion, SongInfo>::Iterator it = _dic_songs.busca(c);
		_duration -= it.valor().duration;
		if (it.valor().inPlaylist) {
			_duration_playlist -= it.valor().duration;
			_playlist.eliminar(it.valor().it_playlist);
		}
		if (it.valor().played)
			_played.eliminar(it.valor().it_played);
		_dic_songs.borra(c);
	}
}

//play: La primera canción de la lista de reproducción abandona
//la lista de reproducción y se registra como reproducida.
//Si la lista es vacía la acción no tiene efecto.

// Registra la reproduccion de una cancion
void iPud::play(){
	// CONSTANTE
	if (!_playlist.esVacia()) {
		DiccionarioHash<Cancion, SongInfo>::Iterator it = _dic_songs.busca(_playlist.ultimo());		
		if (it.valor().played) {
			_played.eliminar(it.valor().it_played);
		}
		_played.pon_ppio(_playlist.ultimo());
		it.valor().it_played = _played.begin();
		it.valor().played = true;
		it.valor().inPlaylist = false;
		_playlist.eliminar(it.valor().it_playlist);
		_duration_playlist -= it.valor().duration;
	}
}

//recent(N) : Obtiene la lista con las N últimas canciones  
//que se han reproducido(mediante la operación play), 
//de la más reciente a la más antigua.
//Si el número de canciones reproducidas es menor que N 
//se devolverán todas.La lista no tiene repeticiones, 
//de manera que si una canción se ha reproducido más 
//de una vez sólo figurará la reproducción más reciente.

// Obtiene la lista con las N últimas canciones que se han reproducido (mediante la operación play), 
// de la más reciente a la más antigua.


Lista<Cancion> iPud::recent(int n){
	// LINEAL
	Lista<Cancion> milista;
	if (!_played.esVacia()) {
		int i = 0;
		Lista<Cancion>::ConstIterator it = _played.cbegin();
		while (it != _played.cend()) {
			if (i >= _played.longitud() - n) {
				milista.pon_final(it.elem());
			}
			it.next();
			++i;
		}
	}
	return milista;
}



int main(){
	
	iPud i;
	Cancion a,b,c,d,e,z;

	i.addSong(a, "Bisbal", 3);
	i.addSong(b, "Chenoa", 2);
	i.addSong(c, "Pitingo", 1);
	i.addSong(d, "Busta", 4);
	i.addSong(e, "Ricky", 5);

	i.addToPlaylist(a);
	i.addToPlaylist(b);
	i.addToPlaylist(a);
	i.addToPlaylist(c);
	i.addToPlaylist(z);

	i.deleteSong(b);
	i.deleteSong(z);

	cout << "total time => " << i.totalTime() << "\n";

	i.play();
	i.play();

	cout << "current => " << i.current() << "\n";
	
	Lista<Cancion> milista = i.recent(5);

	Lista<Cancion>::ConstIterator it = milista.cbegin();
	int cont = 0;

	while (it != milista.cend()) {
		cout << "numero => " << cont << "\n";
		cout << "cancion => " << it.elem() << "\n";
		it.next();
		cont++;
	}

	return 0;
}