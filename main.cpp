#include <iostream>
#include <list>

struct Aluno
{
    int matricula;
    std::string nome, curso;
};

struct Professor
{
    int codigo;
    std::string nome;
};

struct Disciplina
{
    int codigo;
    std::string nome, curso;
    int carga_horaria;
};

struct Turma
{
    Professor* professor;
    std::list<Aluno*>* alunos;
    Disciplina* disciplina;
};

// INCLUIR

Aluno* criar_aluno(int matricula, std::string nome, std::string curso)
{
    Aluno* a = new Aluno;

    a->matricula = matricula;
    a->nome = nome;
    a->curso = curso;

    return a;
}

Professor* criar_professor(int codigo, std::string nome)
{
    Professor* p = new Professor;

    p->codigo = codigo;
    p->nome = nome;

    return p;
}

Disciplina* criar_disciplina(int codigo, std::string curso, std::string nome, int carga_horaria)
{
    Disciplina* d = new Disciplina;

    d->codigo = codigo;
    d->curso = curso;
    d->nome = nome;
    d->carga_horaria = carga_horaria;

    return d;
}

Turma* criar_turma(Professor* p, Disciplina* d)
{
    Turma* t = new Turma;

    t->professor = p;
    t->disciplina = d;
    t->alunos = new std::list<Aluno*>;

    return t;
}

// EXCLUIR

void excluir_aluno(Turma* t, Aluno* a)
{
    std::list<Aluno*>::iterator it;

    for(it = t->alunos->begin(); it != t->alunos->end(); it++)
    {
        if((*it)->matricula == a->matricula)
        {
            t->alunos->erase(it);
            break;
        }
    }

    delete a;
}

void excluir_turma(Turma* t)
{
    std::list<Aluno*>::iterator it;

    for(it = t->alunos->begin(); it != t->alunos->end(); it++)
        delete *it;

    delete t->alunos;
    delete t->professor;
    delete t->disciplina;
    delete t;
}

// OUTRAS

std::list<Aluno*>* matricular_aluno(std::list<Aluno*>* lista, Aluno* a)
{
    lista->push_back(a);
    return lista;
}

void buscar_aluno(Turma* t, int matricula)
{
    bool encontrado = false;
    std::list<Aluno*>::iterator it;

    std::cout << "\nBuscando aluno...\n\n";

    for(it = t->alunos->begin(); it != t->alunos->end(); it++)
    {
        if((*it)->matricula == matricula)
        {
            std::cout << "Nome: " << (*it)->nome << std::endl;
            std::cout << "Matrícula: " << (*it)->matricula << std::endl;
            std::cout << "Curso: " << (*it)->curso << std::endl;
            encontrado = true;
        }
    }

    if(!encontrado)
        std::cout << "\nAluno não encontrado." << std::endl;
}

void visualizar_turma(Turma* t)
{
    std::list<Aluno*>::iterator it;

    std::cout << "\nVisualizando turma...\n\n";
    std::cout << "Disciplina: " << t->disciplina->nome << std::endl;
    std::cout << "Curso: " << t->disciplina->curso << std::endl;
    std::cout << "Carga horária: " << t->disciplina->carga_horaria << std::endl;
    std::cout << "Professor: " << t->professor->nome << std::endl;
    std::cout << "Alunos: " << std::endl;

    for(it = t->alunos->begin(); it != t->alunos->end(); it++)
        std::cout << (*it)->nome << std::endl;
    
    std::cout << std::endl;
}

int main()
{
    //criar alunos
    Aluno* a1 = criar_aluno(1,"Lorenzo", "Ciência da computação");
    Aluno* a2 = criar_aluno(2, "Jordano", "Ciência da computação");
    Aluno* a3 = criar_aluno(3, "Renan", "Ciência da computação");

    //criar professor, disciplina e turma
    Professor* p1 = criar_professor(1, "Leonardo"); 
    Disciplina* d1 = criar_disciplina(1, "Ciência da computação", "Geometria analítica", 60);
    Turma* t1 = criar_turma(p1, d1);

    //matricular alunos em uma turma
    t1->alunos = matricular_aluno(t1->alunos, a1);
    t1->alunos = matricular_aluno(t1->alunos, a2);
    t1->alunos = matricular_aluno(t1->alunos, a3);

    //buscar um aluno em uma turma
    buscar_aluno(t1, 3);

    //visualizar os dados de uma turma
    visualizar_turma(t1);

    //excluir alunos
    excluir_aluno(t1, a1);
    excluir_aluno(t1, a2);
    excluir_aluno(t1, a3);

    //excluir turma
    excluir_turma(t1);
}