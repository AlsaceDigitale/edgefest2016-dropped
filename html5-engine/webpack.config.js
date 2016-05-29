const path = require('path');
const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
    entry: {
        vendor: './client/vendor.js',
        app: './client/app.js'
    },

    output: {
        path: path.join(__dirname, 'client', 'dist'),
        filename: '[name].bundle.js',
        sourceMapFilename: '[name].map',
        chunkFilename: '[id].chunk.js'
    },
    
    module: {
        loaders: [
            { test: /\.js$/, loader: 'babel?presets=es2015' },
            { test: /\.scss$/, loaders: ['style', 'css', 'resolve-url', 'sass'] },
            { test: /bootstrap\/dist\/js\/umd\//, loader: 'imports?jQuery=jquery' },
            { test: /bower_components\/EaselJS\/.*\.js$/, loader: 'imports?this=>window!exports?window.createjs' }
        ]
    },
    
    plugins: [
        new webpack.ResolverPlugin(
            new webpack.ResolverPlugin.DirectoryDescriptionFilePlugin('.bower.json', ['main'])
        ),
        new webpack.optimize.CommonsChunkPlugin({ name: ['app', 'vendor'], minChunks: Infinity }),
        new webpack.NoErrorsPlugin(),
        new webpack.ProvidePlugin({
            'jQuery'       : 'jquery',
            '$'            : 'jquery',
            'jquery'       : 'jquery',
            'Tether'       : 'tether',
            'window.Tether': 'tether'
        }),
        new HtmlWebpackPlugin({ template: path.join(__dirname, 'client', 'index.html') })
    ],

    resolve: {
        modulesDirectories: ['node_modules', 'bower_components'],
        root: [path.join(__dirname, 'client')],
        extensions: ['', '.js']
    },

    devServer: {
        historyApiFallback: true,
        watchOptions: { aggregateTimeout: 300, poll: 1000 }
    },
    
    stats: { colors: true },
    
    devtool: 'source-map'
};
