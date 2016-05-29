const path = require('path');
const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const WebpackBrowserPlugin = require('webpack-browser-plugin');

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
            { test: /\.js$/, loader: 'babel', query: { presets: 'es2015' } },
            { test: /\.scss$/, loaders: ['style', 'css', 'resolve-url', 'sass'] },
            { test: /bootstrap\/dist\/js\/umd\//, loader: 'imports', query: { jQuery: 'jquery' } }
        ]
    },
    
    plugins: [
        new webpack.optimize.CommonsChunkPlugin({ name: ['app', 'vendor'], minChunks: Infinity }),
        new webpack.NoErrorsPlugin(),
        new webpack.ProvidePlugin({
            'jQuery'       : 'jquery',
            '$'            : 'jquery',
            'jquery'       : 'jquery',
            'Tether'       : 'tether',
            'window.Tether': 'tether'
        }),
        new HtmlWebpackPlugin({ template: path.join(__dirname, 'client', 'index.html') }),
        new WebpackBrowserPlugin()
    ],

    resolve: {
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
