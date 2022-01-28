#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "generics.h"
#include "Absyn.H"

/* Certain applications may improve performance by changing the buffer size */
#define BUFFER_INITIAL 2000
/* You may wish to change _L_PAREN or _R_PAREN */
#define _L_PAREN '('
#define _R_PAREN ')'


class PrintAsp : public Visitor
{
 protected:
  std::map<std::string, bool> fluent;
  std::string actionString;
  std::string listLiteralsString;
  std::string literalString;
  std::vector<std::string> varsAction;
  std::vector<std::string> varsListLiteral;
  std::vector<std::string> varsLiteral;
  std::vector<std::string> varsPreds;
  std::vector<std::string> varsListExpr;
  std::vector<std::string> varsExpr;
  std::string predString;
  std::string exprString;
  std::string listExprString;
  std::map<std::string, std::string> m;
  
  std::string expr;
  /* The following are simple heuristics for rendering terminals */
  /* You may wish to change them */
 
 public:
  PrintAsp(void);
  ~PrintAsp(void);
  void print(Visitable* v);
  
  //void openFile(const std::string &name){ f.open(name);}
  //void closeFile(){ f.close();}

  void visitProgram(Program *p); /* abstract class */
  void visitPrg(Prg *p);
  void visitDecl(Decl *p); /* abstract class */
  void visitDef(Def *p);
  void visitExec(Exec *p);
  void visitCaus(Caus *p);
  void visitCausCond(CausCond *p);
  void visitInit(Init *p);
  void visitFinal(Final *p);
  void visitPredicate(Predicate *p); /* abstract class */
  void visitPreds(Preds *p);
  void visitPred(Pred *p);
  void visitLiteral(Literal *p); /* abstract class */
  void visitLitN(LitN *p);
  void visitLit(Lit *p);
  void visitLitE(LitE *p);
  void visitLitNE(LitNE *p);
  void visitAction(Action *p); /* abstract class */
  void visitActs(Acts *p);
  void visitAct(Act *p);
  void visitExp(Exp *p); /* abstract class */
  void visitEAdd(EAdd *p);
  void visitESub(ESub *p);
  void visitEMul(EMul *p);
  void visitEDiv(EDiv *p);
  void visitEMod(EMod *p);
  void visitEInt(EInt *p);
  void visitEIdent(EIdent *p);
  void visitListLiteral(ListLiteral* p);
  void visitListIdent(ListIdent* p);
  void visitListExp(ListExp* p);
  void visitListDecl(ListDecl* p);

  void visitInteger(Integer i){};
  void visitDouble(Double d){};
  void visitChar(Char c){};
  void visitString(String s){};
  void visitIdent(String s){};

  stringstream f;
 protected:

  std::string &justifyVars(std::string &res, std::vector<std::string> &vett){

    sort( vett.begin(), vett.end() );
    vett.erase( unique( vett.begin(), vett.end() ), vett.end() );

    int count = 0;
    for (auto var : vett){
      //std::cout << var <<"\n";
      res += m[var]+"("+var+")";
      if(count != vett.size()-1) res += ", ";
      count++;
    }

    return res;
  }
};

#endif

