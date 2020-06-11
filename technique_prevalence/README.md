# Technique Prevalence

Red Canary publishes an annual Threat Detection Report that is an in-depth look at the most prevalent 
ATT&CK® techniques designed to help you and your team focus on what matters most.
                                                       
To best help the entire security community leverage this research, 
[the Threat Detection Report is published online](https://redcanary.com/threat-detection-report/introduction/) 
and we use this GitHub repository to publish machine-readable technique prevalence information.
 
This data illustrates how often each ATT&CK technique is leveraged in a confirmed threat in our customers' 
environments. It is an array of records that each look like this:

```
  # a unique identifier internal to Red Canary
  # (becomes more relevant when subtechniques are live) 
  id: 881
  
  # the friendly name of the technique
  name: Process Injection
  
  # a link to more information about the technique, most often at `attack.mitre.org`
  link: https://attack.mitre.org/techniques/T1055
  
  # the public, unique technique identifier
  technique_identifier: T1055
  
  # the source of the technique, either `mitre_attack` or `red_canary` (used for internal 
  # techniques that are being submitted for incorporation)
  source: mitre_attack
  source_type: enterprise

  # the prevalence rankings from the research leading to the annual Threat Detection Reports  
  # (techniques that are not highly prevalent are not given a prevalence ranking)
  ranking_2020: 1
  ranking_2019: 20

  # a link to additional research Red Canary has published on the technique
  technique_detail_link: https://redcanary.com/threat-detection-report/techniques/process-injection/
```

## For Red Canary maintainers

To generate this file, see `Portal/ops.rb#public_research_technique_prevalence` to generate the YAML version, then run:

```bash
ruby -e 'require "yaml"; require "json"; File.write("techniques_with_prevalence.json", JSON.pretty_generate(YAML.safe_load(File.read "techniques_with_prevalence.yaml")))'
```
