// PON AQUÍ TU NOMBRE Y APELLIDOS, ASÍ COMO EL NÚMERO DE TU DOCUMENTO IDENTIFICATIVO
// NOMBRE:
// APELLIDOS: 
// DNI / NIE:

#include "lista.h"
#include <string>

using namespace std;

class ECursoYaExiste {};
class EEstudianteYaRegistrado {};
class ESolicitud {};
class EEstudianteNoExiste {};
class ENoHaySolicitudes {};
class ECursoNoExiste {};


typedef string tCurso;
typedef string tEstudiante;

/* La operación 'estudiantes_en_curso'
   devuelve una lista de objetos de esta
   clase. El atributo 'estudiante' de esta clase
   contendrá el identificador del estudiante, y
   el atributo 'num_matricula' su número de
   matricula. */
class DatosEstudiante {
  public:
     tEstudiante estudiante;
     unsigned int num_matricula;
     DatosEstudiante(tEstudiante estudiante, int num_matricula): 
         estudiante(estudiante), num_matricula(num_matricula) {};	 
};

/* La operación 'atiende_solicitud'
   devuelve un objeto de esta clase.
   El atributo 'estudiante' contendrá el
   identificador del estudiante atendido,
   el atributo 'curso' el identificador del
   curso solicitado, y el campo 
   'aceptado' el resultado de 
   la solicitud (si es 'true',
   la matrícula solicitada se habrá realizado,
   y si es 'false', la matrícula solicitada
   se habrá desestimado -no se habrá realizado 
  */
class ResultadoSolicitud {
    public:
      ResultadoSolicitud(tEstudiante estudiante, tCurso curso, bool aceptada):
		  estudiante(estudiante), curso(curso), aceptada(aceptada) {}
	  tEstudiante estudiante;
	  tCurso curso;
	  bool aceptada;
};

class GestionDeMatriculas {
public:
   GestionDeMatriculas();
   void registra_curso(const tCurso& curso, unsigned int plazas);
   void registra_estudiante(const tEstudiante& estudiante);
   void registra_solicitud(const tEstudiante& estudiante, const tCurso& curso);
   void cancela_solicitud(const tEstudiante& estudiante);
   ResultadoSolicitud atiende_solicitud();
   Lista<DatosEstudiante> estudiantes_en_curso(const tCurso& curso) const;  
private:
   // Incluir aquí los detalles relativos a la representación
   
};