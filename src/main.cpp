#include <storm/api/storm.h>
#include <storm/utility/initialize.h>
#include <storm-parsers/api/storm-parsers.h>

typedef storm::models::sparse::Dtmc<double> Dtmc;
typedef storm::modelchecker::SparseDtmcPrctlModelChecker<Dtmc> DtmcModelChecker;

bool check(std::string const& path_to_model, std::string const& property_string) {
    // Assumes that the model is in the prism program language format and parses the program.
    auto program = storm::api::parseProgram(path_to_model);
    // Code snippet assumes a Dtmc
    assert(program.getModelType() == storm::prism::Program::ModelType::DTMC);
    // Then parse the properties, passing the program to give context to some potential variables.
    auto properties = storm::api::parsePropertiesForPrismProgram(property_string, program);
    // Translate properties into the more low-level formulae.
    auto formulae = storm::api::extractFormulasFromProperties(properties);

    // Now translate the prism program into a DTMC in the sparse format.
    // Use the formulae to add the correct labelling.
    auto model = storm::api::buildSparseModel<double>(program, formulae)->template as<Dtmc>();

    // Create a model checker on top of the sparse engine.
    auto checker = std::make_shared<DtmcModelChecker>(*model);
    // Create a check task with the formula. Run this task with the model checker.
    auto result = checker->check(storm::modelchecker::CheckTask<>(*(formulae[0]), true));
    assert(result->isExplicitQuantitativeCheckResult());
    // Use that we know that the model checker produces an explicit quantitative result
    auto quantRes = result->asExplicitQuantitativeCheckResult<double>();
    // Now compare the result at the first initial state of the model with 0.5.
    return quantRes[*model->getInitialStates().begin()] > 0.5;
}

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--help") {
        std::cout << "Storm starter project example binary. " << std::endl;
        std::cout << "Usage: " << std::endl;
        std::cout << argv[0] << " [PRISM MODEL] [PROPERTY STRING]" << std::endl;
        return 0;
    }
    if (argc != 3) {
        std::cout << "Needs exactly 2 arguments. Run --help for info." << std::endl;
        return 1;
    }

    // Init loggers
    storm::utility::setUp();
    // Set some settings objects.
    storm::settings::initializeAll("storm-starter-project", "storm-starter-project");

    // Call function
    auto result = check(argv[1], argv[2]);
    // And print result
    std::cout << "Result > 0.5? " << (result ? "yes" : "no") << std::endl;
}
