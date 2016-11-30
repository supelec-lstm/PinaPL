#ifndef DEF_LOG
#define DEF_LOG

extern int tab_log;

#ifdef LOG

#define PRINT_HEADER	   											\
	cout << FILE_NAME << " :"; 										\
	for(int indice_log = 0; indice_log < tab_log; indice_log++){	\
		cout << "\t";												\
	}																\
	cout << "# ";

#define PRINT_LOG(title) 	\
	PRINT_HEADER			\
	cout << title << endl;

#define PRINT_BEGIN_FUNCTION(title)	\
	tab_log ++;						\
	PRINT_HEADER					\
	cout << title << endl;			\

#define PRINT_END_FUNCTION() tab_log --;

#define PRINT_VECTOR(vector, taille)                    \
    PRINT_HEADER                                        \
    for(int indice1 = 0; indice1 < taille; indice1++){  \
        cout << vector[indice1] << " ";                 \
    }                                                   \
    cout << endl;

#else

#define PRINT_LOG(title)
#define PRINT_BEGIN_FUNCTION(title)
#define PRINT_END_FUNCTION()

#endif //LOG

#endif //DEF_LOG
