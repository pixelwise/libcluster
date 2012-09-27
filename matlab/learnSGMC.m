% The Symmetric Grouped Mixtures Clustering (S-GMC) clustering algorithm.  This
%   function uses the Symmetric Grouped Mixtures Clustering model [1] to 
%   cluster multiple datasets simultaneously with cluster sharing between 
%   datasets. It uses a symmetric Dirichlet prior over the group mixture 
%   weights, and a Gaussian-Wishart prior over the cluster parameters.
%
%  [qZ, weights, means, covariances] = learnSGMC (X, options)
%
% Arguments:
%  - X, {Jx[NxD]} cell array of observation matrices (one cell for each group)
%  - options, structure with members (all are optional):
%     + prior, [double] prior cluster value (1e-5 default)
%     + verbose, [bool] verbose output flag (false default)
%     + sparse, [bool] do fast but approximate sparse VB updates (false default)
%     + threads, [unsigned int] number of threads to use (automatic default)
%
% Returns
%  - qZ, {Jx[NxK]} cell array of assignment probablities
%  - weights, {Jx[1xK]} Group mixture weights
%  - means, {Kx[1xD]} Gaussian mixture means
%  - covariances, {Kx[DxD]} Gaussian mixture covariances
%
% Author: Daniel Steinberg
%         Australian Centre for Field Robotics
%         University of Sydney
%
% Date:   27/09/2012
%
% References:
%  [1] D. M. Steinberg, O. Pizarro, and S. B. Williams, "Clustering Groups of
%      Related Visual Datasets," unpublished, 2011.