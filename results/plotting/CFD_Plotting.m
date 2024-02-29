clc
clear variables
close all

fileNames = {
    % '01_5_5_100_UDS_08'
    % '02_129_129_1000_UDS_08'
    % '03_40_40_1000_QUICK_08'
    '04_40_40_1000_UDS_05'
    };


%% Loading data

Ghia_Solution_U = table2struct(readtable('Ghia_Solution_U.xlsx'));
Ghia_Solution_V = table2struct(readtable('Ghia_Solution_V.xlsx'));

for file_idx = 1:length(fileNames)

    result = readtable(['../' fileNames{file_idx} '.dat'], 'NumHeaderLines', 5);

    x = result.Var1;
    y = result.Var2;
    u = result.Var3;
    v = result.Var4;
    p = result.Var5;

    [x, sort_idx] = sort(x);
    y = y(sort_idx);
    u = u(sort_idx);
    v = v(sort_idx);
    p = p(sort_idx);

    % Create a grid
    [X, Y] = meshgrid(unique(x), unique(y));

    % Reshape states to match the grid
    U = reshape(u, [numel(unique(y)), numel(unique(x))]);
    V = reshape(v, [numel(unique(y)), numel(unique(x))]);
    P = reshape(p, [numel(unique(y)), numel(unique(x))]);

    axis_limit = [
        min(X, [], "all")
        max(X, [], "all")
        min(Y, [], "all")
        max(Y, [], "all")
        ];

    clear x y u v p
    clear sort_idx


    % % Plot states distribution

    figure_state_distribution = figure('Name', 'States distribution', 'NumberTitle', 'off');
    tiledlayout(1, 3);

    states_name = ["P", "U", "V"];
    states_matrix = {P, U, V};

    for state_idx = 1:length(states_matrix)

        nexttile
        hold on
        grid on

        imagesc(X(1,:), Y(:,1), states_matrix{state_idx});

        colorbar;
        title(states_name(state_idx));
        xlabel('X');
        ylabel('Y');
        axis equal;
        axis(axis_limit);

    end

    clear state_idx states_name states_matrix


    % % Plot velocity

    figure_velocity = figure('Name', 'Velocity visualization', 'NumberTitle', 'off');
    tiledlayout(1, 2);

    % Vectorial
    nexttile
    hold on
    grid on

    quiver(X, Y, U, V);

    title('Velocity vectorial field');
    xlabel('X');
    ylabel('Y');
    axis equal;
    axis(axis_limit);

    % Streamlines
    nexttile
    hold on
    grid on

    [verts, averts] = streamslice(X, Y, U, V);
    streamline([verts, averts]);

    title('Velocity streamlines');
    xlabel('X');
    ylabel('Y');
    axis equal;
    axis(axis_limit);

    clear verts averts


    % % Plots for comparison with Ghia's solution

    figure_ghia_comparison = figure('Name', 'Ghia solution comparison', 'NumberTitle', 'off');
    tiledlayout(1, 2);

    % Comparison of u component with Ghia's solution
    nexttile
    hold on;
    grid on;

    plot(U(:, ceil(size(X, 1)/2)), Y(:,1), 'b', 'LineWidth', 2);
    plot([Ghia_Solution_U.Re100], [Ghia_Solution_U.y], 'go', 'LineWidth', 1);
    plot([Ghia_Solution_U.Re400], [Ghia_Solution_U.y], 'yo', 'LineWidth', 2);
    plot([Ghia_Solution_U.Re1000], [Ghia_Solution_U.y], 'ro', 'LineWidth', 2);

    title("u velocity @x=0.5")

    % Comparison of v component with Ghia's solution
    nexttile
    hold on;
    grid on;

    plot(X(1,:), V(ceil(size(Y, 1)/2), :), 'b', 'LineWidth', 2);
    plot([Ghia_Solution_V.x], [Ghia_Solution_V.Re100], 'go', 'LineWidth', 1);
    plot([Ghia_Solution_V.x], [Ghia_Solution_V.Re400], 'yo', 'LineWidth', 2);
    plot([Ghia_Solution_V.x], [Ghia_Solution_V.Re1000], 'ro', 'LineWidth', 2);

    title("v velocity @y=0.5")

end



