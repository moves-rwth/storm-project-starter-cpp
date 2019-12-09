#include <storm/api/storm.h>
#include <storm-parsers/api/storm-parsers.h>
#include <storm-parsers/parser/PrismParser.h>
#include <storm/storage/prism/Program.h>
#include <storm/storage/jani/Property.h>
#include <storm/modelchecker/results/CheckResult.h>
#include <storm/modelchecker/results/ExplicitQuantitativeCheckResult.h>

#include <storm/utility/initialize.h>

typedef storm::models::sparse::Dtmc<double> Dtmc;
typedef storm::modelchecker::SparseDtmcPrctlModelChecker<Dtmc> DtmcModelChecker;

bool check(std::string const& path_to_model, std::string const& property_string) {
    auto program = storm::parser::PrismParser::parse(path_to_model);
    // Code snippet assumes a Dtmc
    assert(program.getModelType() == storm::prism::Program::ModelType::DTMC);
    auto properties = storm::api::parsePropertiesForPrismProgram(property_string, program);
    auto formulae = storm::api::extractFormulasFromProperties(properties);
    auto model = storm::api::buildSparseModel<double>(program, formulae)->template as<Dtmc>();
    auto checker = std::make_shared<DtmcModelChecker>(*model);

    auto result = checker->check(storm::modelchecker::CheckTask<>(*(formulae[0]), true));
    assert(result->isExplicitQuantitativeCheckResult());
    // Use that we know that the model checker produces an explicit quantitative result
    auto quantRes = result->asExplicitQuantitativeCheckResult<double>();

    return quantRes[model->getInitialStates()[0]] > 0.5;
}


int main (int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Needs exactly 2 arguments: model file and property" << std::endl;
        return 1;
    }

    // Init
    storm::utility::setUp();
    storm::settings::initializeAll("storm-starter-project", "storm-starter-project");

    // Call function
    auto result = check(argv[1], argv[2]);

    std::cout << "Result > 0.5? " << (result ? "yes" : "no") << std::endl;
}
