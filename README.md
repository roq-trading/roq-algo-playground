# roq-cpp-algo-template

This is a "framework" to manage the strategies implemented by the `roq-algo` library.

It allows you to run a strategy against live gateways or simulate using event-logs (historical data captured by gateways).

The strategy may be associated with a "reporter" which, upon strategy termination, may output various metrics.
This is useful when measuring the performance of a simulated strategy.

The setup is such that the strategy "legs" have to be defined in a `.toml` file.
This is considered "static" configuration.

Strategy (model) parameters are configured on the command-line as key-value pairs.
This is considered "dynamic" configuration.

The distinction between "static" and "dynamic" configuration is done to support distributed simulations.

## SLURM

SLURM will allow you to pass distinct command-line arguments for each task.

One could then either pass model parameters on the command-line or use the command-line as an indirection to fetch model
parameters from a file.

When launching 100s of tasks, it's more efficient to pass the variation of model parameters on the command-line as
compared to first create 100s of files containing the model parameters.

> Both options are possible since Abseil supports reading command-line flags from file.


## License

The project is released under the terms of the BDS-3 license.
