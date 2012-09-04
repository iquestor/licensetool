
#ifndef LICENSE_H
#define LICENSE_H

/**
 * Generates a license given the limit, company name and the master key.
 * @param limit The limit.
 * @param company_name The company name.
 * @param master_key The master key.
 */
char * generate_license(const unsigned limit, const char * company_name, const char * master_key);

int validate_license(const char * license, unsigned * limit, const char * master_key);

#endif // LICENSE_H
