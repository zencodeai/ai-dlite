// --------------------------------------------------------------------------------
// 
// sample.h
// 
// --------------------------------------------------------------------------------


#ifndef __STORE__
#define __STORE__

// ................................................................................
// Ontologies

#define                                 O_family (0x01000001)

// ................................................................................
// Roles

#define                              R_has_child (0x08000014)
#define                             R_married_to (0x08000017)
#define                             R_has_parent (0x08000028)

// ................................................................................
// Concepts

#define                                  C_being (0x06000002)
#define                                  C_human (0x06000003) // ~animal&being
#define                                 C_animal (0x06000005) // ~human&being
#define                                 C_female (0x06000007) // ~hermaphrodite&~male&animal
#define                          C_hermaphrodite (0x06000009) // ~female&~male&animal
#define                                   C_male (0x0600000b) // ~hermaphrodite&~female&animal
#define                                  C_woman (0x06000010) // ~man&human
#define                                    C_man (0x06000012) // ~woman&human
#define                                 C_parent (0x06000016) // (?married_to/parent|?has_child/human)&human
#define                                 C_mother (0x0600001c) // woman&parent
#define                                 C_father (0x0600001e) // man&parent
#define                                C_husband (0x06000021) // ?married_to/woman&man
#define                                   C_wife (0x06000024) // ?married_to/man&woman
#define                                C_married (0x06000027) // ?married_to/human&human
#define                                  C_child (0x0600002b) // ?has_parent/human&human
#define                                    C_son (0x0600002d) // man&child
#define                               C_daughter (0x0600002f) // woman&child
#define                           C_grand_parent (0x06000032) // ?has_child/parent&human
#define                           C_grand_father (0x06000034) // grand_parent&man
#define                           C_grand_mother (0x06000036) // grand_parent&woman

#endif //__STORE__
