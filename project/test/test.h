/*
 *
 * test.db
 *
 * Test ontology store
 *
 * 2010/02/12 23:02:10
 *
 */

#ifndef __ONTOLOGY__
#define __ONTOLOGY__

#define SYM_COUNTER ((unsigned long) 1054)


/* -------------------------------------------------------------------------- */
/* -- Ontologies                                                              */

#define O_FAMILY_TXT                   ((unsigned long) 0x010003E8)


/* -------------------------------------------------------------------------- */
/* -- Roles                                                                   */

#define R_has_child                    ((unsigned long) 0x080003FC)
#define R_married_to                   ((unsigned long) 0x080003FE)
#define R_has_parent                   ((unsigned long) 0x08000410)


/* -------------------------------------------------------------------------- */
/* -- Concepts                                                                */

#define C_x_b_c1                       ((unsigned long) 0x06000001)
#define C_x_b_c2                       ((unsigned long) 0x06000002)
#define C_x_b_c3                       ((unsigned long) 0x06000003)
#define C_animal                       ((unsigned long) 0x060003E9) /* being&~human */
#define C_being                        ((unsigned long) 0x060003EA)
#define C_human                        ((unsigned long) 0x060003EB) /* being&~animal */
#define C_male                         ((unsigned long) 0x060003EE) /* animal&~female&~hermaphrodite */
#define C_female                       ((unsigned long) 0x060003EF) /* animal&~male&~hermaphrodite */
#define C_hermaphrodite                ((unsigned long) 0x060003F1) /* animal&~male&~female */
#define C_man                          ((unsigned long) 0x060003F7) /* human&~woman */
#define C_woman                        ((unsigned long) 0x060003F8) /* human&~man */
#define C_parent                       ((unsigned long) 0x060003FB) /* human&(?has_child/human|?married_to/parent) */
#define C_mother                       ((unsigned long) 0x06000402) /* parent&woman */
#define C_father                       ((unsigned long) 0x06000404) /* parent&man */
#define C_husband                      ((unsigned long) 0x06000406) /* man&?married_to/woman */
#define C_wife                         ((unsigned long) 0x06000409) /* woman&?married_to/man */
#define C_married                      ((unsigned long) 0x0600040C) /* human&?married_to/human */
#define C_child                        ((unsigned long) 0x0600040F) /* human&?has_parent/human */
#define C_son                          ((unsigned long) 0x06000413) /* child&man */
#define C_daughter                     ((unsigned long) 0x06000415) /* child&woman */
#define C_grand_parent                 ((unsigned long) 0x06000417) /* human&?has_child/parent */
#define C_grand_father                 ((unsigned long) 0x0600041A) /* man&grand_parent */
#define C_grand_mother                 ((unsigned long) 0x0600041C) /* woman&grand_parent */

#endif /*__ONTOLOGY__*/
