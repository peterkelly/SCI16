/***************************************************************************

	Module     :
	
	Subprogram : NLP (Natural Language Parser Interface)
	
	Program    : SCI (Script Interpreter for Sierra On-line games)
	
	Author/Date: Pablo Ghenis for Sierra On-line, July 1988
	
	Platform   : Portable C, any 16+ bit micro with 512k+ RAM
	
	Purpose    :
	
	

***************************************************************************/



#ifndef	TYPES_H
#include	"types.h"
#endif

#ifndef	DLL_H
#include	"dll.h"
#endif

#ifndef	NLSYMS_H
#include	"syms.h"
#endif

#ifndef	PARSE_H
#include	"parse.h"
#endif

#ifndef	VOCAB_H
#include	"vocab.h"
#endif

#ifndef	PRINTP_H
#include	"print.h"
#endif



NLSYM NLSYMTAB[] =
     {
     "NULL",   
     "(",
     ")",
     " ",					//	"VERB",
     " ",					//	"NOUN", 
     " ",					//	"ART",
     " ",					//	"ADJ",
	  " ",					//	"POS",
	  " ",					//	"PRON", 
     " ",					//	"CONJ",
     " ",					//	"AUXV",
     " ",					//	"ADV",
     " ",					//	"ASS", 
     " ",					//	"CNoun",
     " ",					//	"CAdj",
     " ",					//	"CVerb",
     " ",					//	"VerbP",   
     " ",					//	"NounP",
	  " ",					//	"AssocP",
	  " ",					//	"Sentence",
	  " ",					//	"EOL",
	  "Root",
	  "DObj",
	  "IObj",
	  "<",					// "Mod", 
	  "Ignored",
	  " ",					//	"VOC",
	  " ",					//	"SPEC",
	  " ",					//	"SPEC2",
	  " ",					//	"PH",
	  " ",					//	"PH2",
	  ">",					//	"MORE",
	  " ",					//	"UNIT",
	  " ",					//	"PNCT", 
	  " ",					//	"EMPT",
	  "OR",
	  " ",					//	"OR2",
	  " ",					//	"ATM",
	  "OPT",
	  " ",					//	"WRD",
	  " ",					//	"PUT",
	  " ",					//	"NUM",
     "EOGRAMMAR"
     };
     



NLTOK sym_to_tok(sym,symtab)

	NLSYM  sym;
	NLSYM* symtab;
{
  NLTOK i, result;

  for(i=1,result=0;
      *symtab[i] && result==0;
      i++)
  {
     if (strcmp(sym,symtab[i])==0) result=i;
  }

  if (!result)
  {
     /* sprintf(message,
                "%s not symbol!",sym); 
        Alert(message);
     */
  }

  return result;
}

bool tok_to_sym(tok, symtab, result)

	NLTOK  tok;
	NLSYM* symtab;
	NLSYM  result;
{
   bool found=TRUE;
   char tmp[20];
   *result='\0';

   if ( tok>MINNLTOKEN && tok<MAXNLTOKEN ) /* kludge! */
      strbcat(result, symtab[tok-MINNLTOKEN], NLSYMSIZE);
   
   switch (tok)
   {
      case VERB:       strbcat(result, "=VERB", NLSYMSIZE); break;
      case ADV:        strbcat(result, "=ADV", NLSYMSIZE); break;
      case AUXV:       strbcat(result, "=AUXV", NLSYMSIZE); break;
      case NOUN:       strbcat(result, "=NOUN", NLSYMSIZE); break;
      case PRON:       strbcat(result, "=PRON", NLSYMSIZE); break;
      case ADJ:        strbcat(result, "=ADJ", NLSYMSIZE); break;
      case ART:        strbcat(result, "=ART", NLSYMSIZE); break;
      case POS:        strbcat(result, "=POS", NLSYMSIZE); break;
      case ASS:        strbcat(result, "=ASS", NLSYMSIZE); break;
      case CONJ:       strbcat(result, "=CONJ", NLSYMSIZE); break;
   }

   switch (tok)
   {
      case RUNON:      strbcat(result, "=RNON", NLSYMSIZE); break;
      case MODIFIES:   strbcat(result, "=MODSD", NLSYMSIZE); break;
      case NEXTPART:   strbcat(result, "=NXTSD", NLSYMSIZE); break;
      case LEFTPAREN:  strbcat(result, "=LP", NLSYMSIZE); break;
      case RIGHTPAREN: strbcat(result, "=RP", NLSYMSIZE); break;
      case OPTBEGIN:   strbcat(result, "=OPTB", NLSYMSIZE); break;
      case OPTEND:     strbcat(result, "=OPTE", NLSYMSIZE); break;
      case ORSAID:     strbcat(result, "=ORSD", NLSYMSIZE); break;
      case ANDSAID:    strbcat(result, "=ANDSD", NLSYMSIZE); break;
      case NUMBER:     strbcat(result, "=NUMSD", NLSYMSIZE); break;
      case METAEND:    strbcat(result, "=M-END", NLSYMSIZE); break;
   }

   switch (tok)
   {
      case NLRNON:     strbcat(result, "=>", NLSYMSIZE); break;
      case NLLESS:     strbcat(result, "=<", NLSYMSIZE); break;
      case NLSLSH:     strbcat(result, "=/", NLSYMSIZE); break;
      case NLLP:       strbcat(result, "=(", NLSYMSIZE); break;
      case NLRP:       strbcat(result, "=)", NLSYMSIZE); break;
      case NLLB:       strbcat(result, "=[", NLSYMSIZE); break;
      case NLRB:       strbcat(result, "=]", NLSYMSIZE); break;
      case NLCOMA:     strbcat(result, "=,", NLSYMSIZE); break;
      case NLAND:      strbcat(result, "=NLAND", NLSYMSIZE); break;
      case NLEOSPEC:   strbcat(result, "=NLEOSPEC", NLSYMSIZE); break;
   }   
   if (*result == '\0') 
   {
		ift[SPRINTF].function(tmp,"=x%4x=%5d",tok,tok);
      strbcat(result,tmp, NLSYMSIZE);
      found = FALSE;
   }

   return found;
}

