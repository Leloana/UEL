package br.uel.Prova1ConsumidorMarceloFerreira;

import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;

public class ServletInitializer extends SpringBootServletInitializer {

	@Override
	protected SpringApplicationBuilder configure(SpringApplicationBuilder application) {
		return application.sources(Prova1ConsumidorMarceloFerreiraApplication.class);
	}

}
