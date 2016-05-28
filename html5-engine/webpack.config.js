const path = require('path');
const webpack = require('webpack');

module.exports = {
    entry: './client/app.js',
    
    output: {
        path: path.join(__dirname, 'client', 'dist'),
        filename: 'bundle.js'
    },
    
    module: {
        loaders: [
            { test: /\.js$/, loader: 'babel-loader', query: { presets: 'es2015' } }
        ]
    },
    
    plugins: [
        new webpack.NoErrorsPlugin()
    ],

    devServer: {
        historyApiFallback: true,
        watchOptions: { aggregateTimeout: 300, poll: 1000 }
    },
    
    stats: { colors: true },
    
    devtool: 'source-map'
};
