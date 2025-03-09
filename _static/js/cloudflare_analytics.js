// source/_static/js/cloudflare_analytics.js
(function() {
    var script = document.createElement('script');
    script.defer = true;
    script.src = 'https://static.cloudflareinsights.com/beacon.min.js';
    script.setAttribute('data-cf-beacon', '{"token": "1759cfae2eab4ff6b2f3ac7339eab4e5"}');
    document.head.appendChild(script);
})();