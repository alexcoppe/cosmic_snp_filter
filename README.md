# cosmic_snp_filter

### Remove COSMIC SNP variants from a VCF file

Given a VCF file annotated with both [dbSNP](https://www.ncbi.nlm.nih.gov/snp/) and [COSMIC](https://cancer.sanger.ac.uk/cosmic), it removes the SNPs present in the CosmicCodingMuts84.vcf or CosmicNonCodingVariants.vcf files.
The problem comes from the fact that the VCF annotated with [dbSNP](https://www.ncbi.nlm.nih.gov/snp/) contains SNPs that could also be genetically dangerous and they should not be thrown-away.

The COSMIC VCFs, both the coding and non coding, are not freely available for everyone. You should sign up to [COSMIC](https://cancer.sanger.ac.uk/cosmic) using your university email. [COSMIC](https://cancer.sanger.ac.uk/cosmic) data is completely free to academic research communities, but commercial users should contact [COSMIC](https://cancer.sanger.ac.uk/cosmic) for licences which are priced according to organisation size.

### Usage

The VCF to be filtered shoud be annotated with COSMIC using [SnpSift](http://snpeff.sourceforge.net/SnpSift.html) software:

```
$ java -Xmx4g -jar /tmp/snpEff/SnpSift.jar annotate All_20180418.vcf.gz  starting.vcf  > dbsnp_annotated.vcf
$ java -Xmx4g -jar /tmp/snpEff/SnpSift.jar annotate CosmicCodingMuts.vcf.gz  dbsnp_annotated.vcf  > cosmic_annotated.vcf
```

Then you can use the program:

```
$ cosmic_snp_filter CosmicNonCodingVariants.vcf cosmic_annotated.vcf > cosmic_annotated_with_no_snps.vcf
```

The -h options shows the help:

```
$ cosmic_snp_filter -h
Usage: cosmic_snp_filter  [OPTION]... COSMIC_VCF VCF_to_filter
  -h	show help options
```

### Licence

DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE, version 2, December 2004.

<a href="http://www.wtfpl.net/"><img
       src="http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-1.png"
       width="88" height="31" alt="WTFPL" />
</a>
