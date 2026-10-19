#include "Catalog.hpp"
#include "CLI.hpp"


int main() {
    Catalog catalog;
    CLI cat(catalog);

    cat.start();

    return 0;
}
