clc
clear variables
close all

fileNames = {
    '01_test'
    '02_40_40_100_UDS_SECOND_08_08'
    '03_40_40_400_UDS_SECOND_008_008'
    '04_40_40_1000_UDS_SECOND_008_008'
    '05_40_40_1000_CDS_SECOND_008_008'
    '06_40_40_1000_QUICK_SECOND_008_008'
    '07_80_80_1000_UDS_SECOND_008_008'
    '08_80_80_1000_CDS_SECOND_008_008'
    '09_80_80_1000_QUICK_SECOND_008_008'
    '10_129_129_1000_QUICK_FOURTH_008_008'
    };

plots = true * [0 1];


%% Loading data

Ghia_Solution_U = table2struct(readtable('Ghia_Solution_U.xlsx'));
Ghia_Solution_V = table2struct(readtable('Ghia_Solution_V.xlsx'));

if(plots(1) == true)
    for file_idx = 1:length(fileNames)
        close all

        result = readtable(['../' fileNames{file_idx} '.dat'], 'NumHeaderLines', 6);

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

        plot(U(:, ceil(size(X, 1)/2)), Y(:,1), 'k', 'LineWidth', 2);
        plot([Ghia_Solution_U.Re100], [Ghia_Solution_U.y], 'go');
        plot([Ghia_Solution_U.Re400], [Ghia_Solution_U.y], 'bo');
        plot([Ghia_Solution_U.Re1000], [Ghia_Solution_U.y], 'ro');

        title("u velocity @x/LX=0.5")
        legend("u velocity @x/LX=0.5", ...
            "Ghia (Re = 100)", ...
            "Ghia (Re = 400)", ...
            "Ghia (Re = 1000)", ...
            "Location", "best")

        % Comparison of v component with Ghia's solution
        nexttile
        hold on;
        grid on;

        plot(X(1,:), V(ceil(size(Y, 1)/2), :), 'k', 'LineWidth', 2);
        plot([Ghia_Solution_V.x], [Ghia_Solution_V.Re100], 'go');
        plot([Ghia_Solution_V.x], [Ghia_Solution_V.Re400], 'bo');
        plot([Ghia_Solution_V.x], [Ghia_Solution_V.Re1000], 'ro');

        title("v velocity @y/LY=0.5")
        legend("v velocity @y/LY=0.5", ...
            "Ghia (Re = 100)", ...
            "Ghia (Re = 400)", ...
            "Ghia (Re = 1000)", ...
            "Location", "best")

        disp(fileNames{file_idx})
        disp('Press a key for the next result')
        pause;

    end
end


%% Residual analysis

if(plot(2) == true)

    figure_ghia_comparison = figure('Name', 'Residual analysis', 'NumberTitle', 'off');

    nexttile
    hold on
    grid on

    for file_idx = 1:length(fileNames)

        fileID = fopen(['../' fileNames{file_idx} '.dat'], 'r');

        % File name
        line = fgetl(fileID)

        RE = sscanf(fgetl(fileID), 'RE: %f');
        iterations = sscanf(fgetl(fileID), 'ITERATIONS: %d');

        residuals_str = strsplit(fgetl(fileID), ' ');
        % Skip the first element, it's just 'RESIDUALS:'
        residuals = cellfun(@str2double, residuals_str(2:end));

        fclose(fileID);

        length(1:50:iterations)
        length(residuals)

        plot(0:50:iterations, residuals, "LineWidth", 2);

    end

    yline(1e-5,'--', 'Tolerance')

    title("Residual analysis");
    legend(fileNames, "Interpreter", "none")

    clear residuals_str

end






