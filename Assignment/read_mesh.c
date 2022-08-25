#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

typedef struct point3d_vector point3d_vector_t;
typedef struct point3d point3d_t;
typedef struct face face_t;
typedef struct face_vector face_vector_t;

#define SUCCESS 1

struct point3d
{
    float x;
    float y;
    float z;
};

struct point3d_vector
{
    struct point3d** p_arr;
    unsigned long long int size; 
    
};

struct face
{
    int a;
    int b;
    int c;

};

struct face_vector
{
    struct face** p_arr;
    unsigned long long int size;
    struct point3d_vector* p_point3d_vec;

};

point3d_vector_t* create_point3d_vector();
int append_to_point3d_vector(point3d_vector_t* p_vec, float x, float y, float z);
int destroy_point3d_vector(point3d_vector_t** pp_vec);
void show_point3d_vector(point3d_vector_t* p_vec);

face_vector_t* create_face_vector();
int append_to_face_vector(face_vector_t* p_vec, int a, int b, int c);
int destroy_face_vector(face_vector_t** pp_vec);
void show_face_vector(face_vector_t* p_vec);



int read_mesh_file(char* mesh_file_name,face_vector_t* p_face_vec);

int main(int argc, char* argv[])
{
    face_vector_t* p_face_vec = NULL;
    int status = 0;

    if( argc != 2)
    {
        printf("Usage: %s <mesh_file_name>", argv[0]);
        exit(1);
    }
    p_face_vec = create_face_vector();

    status = read_mesh_file(argv[1], p_face_vec);
    assert(status == SUCCESS);
    show_face_vector(p_face_vec);
}


int read_mesh_file(char* mesh_file_name, face_vector_t* p_face_vec)
{
    FILE *fp = NULL;
    int line_length = 255;
    char line[255];
    char* str_tok;
    float x, y, z;
    int a, b, c;


    printf("Opening file %s\n",mesh_file_name);
    fp = fopen(mesh_file_name, "r");
    if(fp == NULL)
    {
        fprintf(stderr, "File not found or not readable");
        exit(EXIT_FAILURE);
    }

    printf("Reading 3D points....\n");

    while(fgets(line, line_length, fp))
    {   
        if(line[0] == 'f')
        {
            printf("All 3D points are added to vector \n");
            break;
        }
        else
        {
            str_tok = strtok(line, " ");
            /* ignore first token as it will be f or v we have already checked that it is f. We are assuming that it is v*/
            str_tok = strtok(NULL, " ");
            x = atof(str_tok);
            str_tok = strtok(NULL, " ");
            y = atof(str_tok);
            str_tok = strtok(NULL, " ");
            z = atof(str_tok);

            append_to_point3d_vector(p_face_vec->p_point3d_vec, x, y, z);
        } 

    }

    printf("Reading facess now....\n");
    do
    {
        
        str_tok = strtok(line, " ");
        /* ignore first token as it will be f or v we have already checked that it is f. We are assuming that it is v*/
        str_tok = strtok(NULL, " ");
        a = atoi(str_tok);
        str_tok = strtok(NULL, " ");
        b = atoi(str_tok);
        str_tok = strtok(NULL, " ");
        c = atoi(str_tok);

        append_to_face_vector(p_face_vec, a, b, c);
    }while (fgets(line, line_length, fp));
    printf("All faces are added to vector\n");

    fclose(fp);
    fp = NULL;
    return(SUCCESS);
}


point3d_vector_t* create_point3d_vector()
{
    point3d_vector_t* p_vector;
    p_vector = (point3d_vector_t*)malloc(sizeof(point3d_vector_t));
    p_vector->p_arr = NULL;
    p_vector->size = 0;
    return(p_vector);
}

int append_to_point3d_vector(point3d_vector_t* p_vec, float x, float y, float z)
{
    point3d_t* p_point3d;

    p_point3d = (point3d_t*) malloc(sizeof(point3d_t));
    p_point3d->x = x;
    p_point3d->y = y;
    p_point3d->z = z;
    p_vec->p_arr = (point3d_t**)realloc(p_vec->p_arr, ((p_vec->size) + 1) * sizeof(point3d_t*) );
    p_vec->p_arr[p_vec->size] = p_point3d;
    p_vec->size += 1;

    return(SUCCESS);
}

int destroy_point3d_vector(point3d_vector_t** pp_vec)
{
    int i;
    point3d_vector_t* p_vec = NULL;
    p_vec = *pp_vec;
    
    for(i=0;i<p_vec->size; i++)
    {
        free(p_vec->p_arr[i]);
    }
    
    free(p_vec);
    pp_vec = NULL;
    return(SUCCESS);

}

void show_point3d_vector(point3d_vector_t* p_vec)
{
    int i =0;
    for(i=0;i<p_vec->size; i++)
    {
        printf("%f %f %f", p_vec->p_arr[i]->x, p_vec->p_arr[i]->y, p_vec->p_arr[i]->z);
    }

}

face_vector_t* create_face_vector()
{
    face_vector_t* p_face_vec = NULL;
    p_face_vec = (face_vector_t*) malloc(sizeof(face_vector_t));

    p_face_vec->p_arr = NULL;
    p_face_vec->size = 0;
    p_face_vec->p_point3d_vec = create_point3d_vector();
    return(p_face_vec);
}

int append_to_face_vector(face_vector_t* p_vec, int a, int b, int c)
{
    face_t* p_face = NULL;

    p_face =  (face_t*)malloc(sizeof(face_t));
    p_face->a = a;
    p_face->b = b;
    p_face->c = c;
    p_vec -> p_arr = (face_t**) realloc(p_vec->p_arr, ((p_vec->size) + 1) * sizeof(face_t*));

    p_vec->p_arr[p_vec->size] = p_face;
    p_vec->size += 1;

    return SUCCESS;
}

int destroy_face_vector(face_vector_t** pp_vec)
{
    int i;
    face_vector_t* p_vec = *pp_vec;
    for(i=0;i<p_vec->size; i++)
    {
        free(p_vec->p_arr[i]);
    }
    free(p_vec);
    pp_vec = NULL;
    return(SUCCESS);
}

void show_face_vector(face_vector_t* p_vec)
{
    int i;
    for(i=0; i<p_vec->size; i++)
    {
        printf("Face number %d\n", i);
        printf("Face details \n");
        printf("A->%d B->%d C->%d \n", p_vec->p_arr[i]->a,p_vec->p_arr[i]->b,p_vec->p_arr[i]->c);
        printf("A cordinate x details %f\n", p_vec->p_point3d_vec->p_arr[((p_vec->p_arr[i]->a)-1)]->x);        
        printf("A cordinate y details %f\n", p_vec->p_point3d_vec->p_arr[((p_vec->p_arr[i]->a)-1)]->y);        
        printf("A cordinate z details %f\n", p_vec->p_point3d_vec->p_arr[((p_vec->p_arr[i]->a)-1)]->z);        

        printf("B cordinate x details %f\n", p_vec->p_point3d_vec->p_arr[((p_vec->p_arr[i]->b)-1)]->x);        
        printf("B cordinate y details %f\n", p_vec->p_point3d_vec->p_arr[((p_vec->p_arr[i]->b)-1)]->y);        
        printf("B cordinate z details %f\n", p_vec->p_point3d_vec->p_arr[((p_vec->p_arr[i]->b)-1)]->z);        


        printf("C cordinate x details %f\n", p_vec->p_point3d_vec->p_arr[((p_vec->p_arr[i]->c)-1)]->x);        
        printf("C cordinate y details %f\n", p_vec->p_point3d_vec->p_arr[((p_vec->p_arr[i]->c)-1)]->y);        
        printf("C cordinate z details %f\n", p_vec->p_point3d_vec->p_arr[((p_vec->p_arr[i]->c)-1)]->z);        
    }
}

