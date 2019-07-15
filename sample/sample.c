/*emcc sample.c -s "EXPORTED_FUNCTIONS=['_add','call_import_from_outside_environment']" -s ERROR_ON_UNDEFINED_SYMBOLS=0*/

int add(int a, int b) {
  return a + b;
}

int import_from_outside_environment(int);

void call_import_from_outside_environment() {
  import_from_outside_environment(1);
}