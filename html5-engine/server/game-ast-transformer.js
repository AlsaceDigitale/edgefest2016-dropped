const availableLibs = ['edgefest2016', 'easel', 'three'];

export function makePlugin(gameName) {
    const expectedExports = { 'ENTER': true, 'LOOP': true, 'LEAVE': true, 'UPDATEKEYS': true };

    return function({ types: t }) { return { visitor: {
        ImportDeclaration(path) {
            let stmt = path.node;
            let moduleName = path.node.source.value;
            if(availableLibs.indexOf(moduleName) < 0) return;

            let declarators = [];

            for(let specifier of stmt.specifiers) {
                declarators.push(
                    t.variableDeclarator(
                        t.identifier(specifier.local.name),
                        t.identifier(
                            ('__engine_import.' + moduleName) +
                            (specifier.imported ? ('.' + specifier.imported.name) : '')
                        )
                    )
                );
            }

            path.replaceWith(
                t.variableDeclaration('const', declarators)
            );
        },

        ExportNamedDeclaration(exportPath) {
            let exportStmt = exportPath.node;

            function mkEngineExport(exported, expression) {
                return t.expressionStatement(
                    t.callExpression(
                        t.identifier('__engine_export'), [
                            t.stringLiteral(gameName),
                            t.stringLiteral(exported),
                            expression
                        ]
                    )
                );
            }

            exportPath.traverse({
                ExportSpecifier(specPath) {
                    let specStmt = specPath.node;

                    if(!(specStmt.exported.name in expectedExports)) return;

                    if(expectedExports[specStmt.exported.name] === false) {
                        throw new Error(`${specStmt.exported.name} should be exported only once.`);
                    } else expectedExports[specStmt.exported.name] = false;

                    specPath.remove();

                    exportPath.insertAfter(
                        mkEngineExport(
                            specStmt.exported.name,
                            t.identifier(specStmt.local.name)
                        )
                    );

                    if(!exportStmt.specifiers.length) {
                        exportPath.remove();
                    }
                },

                FunctionDeclaration(funcDecPath) {
                    let funcStmt = funcDecPath.node;

                    if(!(funcStmt.id.name in expectedExports)) return;

                    if(expectedExports[funcStmt.id.name] === false) {
                        throw new Error(`${funcStmt.id.name} should be exported only once.`);
                    } else expectedExports[funcStmt.id.name] = false;

                    exportPath.replaceWith(
                        mkEngineExport(
                            funcStmt.id.name,
                            t.functionExpression(funcStmt.id, funcStmt.params, funcStmt.body)
                        )
                    );
                }
            });
        }
    }}};
}
